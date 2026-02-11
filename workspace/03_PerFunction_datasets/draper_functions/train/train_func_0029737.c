eraAnpm(double a)


{
   double w;


   w = fmod(a, ERFA_D2PI);
   if (fabs(w) >= ERFA_DPI) w -= ERFA_DSIGN(ERFA_D2PI, a);

   return w;

}
