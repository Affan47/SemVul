Angle2D(double x1, double y1, double x2, double y2)
{
   double dtheta,theta1,theta2;

   theta1 = atan2(y1,x1);
   theta2 = atan2(y2,x2);
   dtheta = theta2 - theta1;
   while (dtheta > PI)
      dtheta -= TWOPI;
   while (dtheta < -PI)
      dtheta += TWOPI;

   return(dtheta);
}
