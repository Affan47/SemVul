eraPn(double p[3], double *r, double u[3])


{
   double w;


   w = eraPm(p);
   if (w == 0.0) {


      eraZp(u);

   } else {


      eraSxp(1.0/w, p, u);
   }


   *r = w;

   return;

}
