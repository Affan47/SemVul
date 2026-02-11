calculateGravityAndEnergy(double gravity,double sunEnergy,
                                           double mult)
{
   double nx,ny,ex,ey,abs_2,phi,sq,eg;

   if(!stopped)
   {
      ex=x()+center().x()-scene()->width()/2.0;
      ey=y()+center().y()-scene()->height()/2.0;

      abs_2=ex*ex+ey*ey;
      sq=sqrt(abs_2);

      if ( explodes() && (sq<20) )
         stopped = true;
      else
      {
         nx=ex/sq;
         ny=ey/sq;
         eg=gravity*mult;
         setVelocity(xVelocity()-eg*nx/abs_2,
                     yVelocity()-eg*ny/abs_2);
         if(hitpoints!=0)
         {
            if(energy<99.8)
            {
               phi=rectToAngle(nx,ny);
               energy+=fabs(sunEnergy*mult/(abs_2)*cos(phi+rotation));
            }
         }
      }
   }
}
