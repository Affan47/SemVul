flam3_calc_newrgb(double *cbuf, double ls, double highpow, double *newrgb) {

   int rgbi;
   double newls,lsratio;
   double newhsv[3];
   double a, maxa=-1.0, maxc=0;
   double adjhlp;

   if (ls==0.0 || (cbuf[0]==0.0 && cbuf[1]==0.0 && cbuf[2]==0.0)) {
      newrgb[0] = 0.0;
      newrgb[1] = 0.0;
      newrgb[2] = 0.0;
      return;
   }


   for (rgbi=0;rgbi<3;rgbi++) {
      a = ls * (cbuf[rgbi]/PREFILTER_WHITE);
      if (a>maxa) {
         maxa = a;
         maxc = cbuf[rgbi]/PREFILTER_WHITE;
      }
   }


   if (maxa>255 && highpow>=0.0) {
      newls = 255.0/maxc;
      lsratio = pow(newls/ls,highpow);


      for (rgbi=0;rgbi<3;rgbi++)
         newrgb[rgbi] = newls*(cbuf[rgbi]/PREFILTER_WHITE)/255.0;


      rgb2hsv(newrgb,newhsv);
      newhsv[1] *= lsratio;
      hsv2rgb(newhsv,newrgb);

      for (rgbi=0;rgbi<3;rgbi++)
         newrgb[rgbi] *= 255.0;

   } else {
      newls = 255.0/maxc;
      adjhlp = -highpow;
      if (adjhlp>1)
         adjhlp=1;
      if (maxa<=255)
         adjhlp=1.0;


      for (rgbi=0;rgbi<3;rgbi++)
         newrgb[rgbi] = ((1.0-adjhlp)*newls + adjhlp*ls)*(cbuf[rgbi]/PREFILTER_WHITE);


   }
}
