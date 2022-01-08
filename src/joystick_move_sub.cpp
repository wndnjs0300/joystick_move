#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
float linear=0.0;
float angular=0.0;
void linearCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
 linear= msg->axes[1];
 angular= msg->axes[3];
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joystick_move_sub");
  ros::NodeHandle nh;

  ros::Subscriber sub1 = nh.subscribe("joy", 1000, linearCallback);

  ros::Publisher turtle_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    msg.linear.x = linear;
    msg.angular.z= angular*1.5;

    turtle_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
