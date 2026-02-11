flam3_create_temporal_filter(int numsteps, int filter_type, double filter_exp, double filter_width,
                                    double **temporal_filter, double **temporal_deltas) {

   double maxfilt = 0.0;
   double sumfilt = 0.0;
   double slpx,halfsteps;
   double *deltas, *filter;

   int i;


   deltas = (double *)malloc(numsteps*sizeof(double));
   filter = (double *)malloc(numsteps*sizeof(double));


   if (numsteps==1) {
      deltas[0] = 0;
      filter[0] = 1.0;
      *temporal_deltas = deltas;
      *temporal_filter = filter;
      return(1.0);
   }


   for (i = 0; i < numsteps; i++)
      deltas[i] = ((double)i /(double)(numsteps - 1) - 0.5)*filter_width;


   if (flam3_temporal_exp == filter_type) {

      for (i=0; i < numsteps; i++) {

         if (filter_exp>=0)
            slpx = ((double)i+1.0)/numsteps;
         else
            slpx = (double)(numsteps - i)/numsteps;


         filter[i] = pow(slpx,fabs(filter_exp));


         if (filter[i]>maxfilt)
            maxfilt = filter[i];
      }

   } else if (flam3_temporal_gaussian == filter_type) {

      halfsteps = numsteps/2.0;
      for (i=0; i < numsteps; i++) {


         filter[i] = flam3_spatial_filter(flam3_gaussian_kernel,
                           flam3_spatial_support[flam3_gaussian_kernel]*fabs(i - halfsteps)/halfsteps);

         if (filter[i]>maxfilt)
            maxfilt = filter[i];
      }

   } else {

      for (i=0; i < numsteps; i++)
         filter[i] = 1.0;

	   maxfilt = 1.0;

   }


   for (i=0;i<numsteps;i++) {
      filter[i] /= maxfilt;
      sumfilt += filter[i];
   }

   sumfilt /= numsteps;

   *temporal_deltas = deltas;
   *temporal_filter = filter;

   return(sumfilt);
}
