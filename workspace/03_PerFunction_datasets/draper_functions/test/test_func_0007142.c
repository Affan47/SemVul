tandeg (angle)

const double angle;

{
   double resid;

   resid = fmod(angle,360.0);
   if (resid == 0.0 || fabs(resid) == 180.0) {
      return 0.0;
   } else if (resid == 45.0 || resid == 225.0) {
      return 1.0;
   } else if (resid == -135.0 || resid == -315.0) {
      return -1.0;
   }

   return tan(angle*d2r);
}
