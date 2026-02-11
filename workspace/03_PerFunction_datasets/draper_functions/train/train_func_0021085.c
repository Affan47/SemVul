get_1D_spline(
                  int     knsp,

                  double  **spline)
{
   unsigned int    i=0;
   double          tmp=0.0;

   *spline = (double *) my_calloc(ksp2sz(knsp),sizeof(double));
   for (i=0; i<(knsp-1); i++)
   {
      tmp = ((double) i+1) / ((double) knsp);
      (*spline)[i] = (1.0/6.0) * tmp*tmp*tmp;
   }
   for (i=(knsp-1); i<(2*knsp); i++)
   {
      tmp = ((double) i+1) / ((double) knsp);
      (*spline)[i] = (2.0/3.0) - 0.5*(2.0-tmp)*(2.0-tmp)*tmp;
   }
   for (i=(2*knsp); i<(4*knsp-1); i++)
   {
     (*spline)[i] = (*spline)[(4*knsp-2)-i];
   }

   return(ksp2sz(knsp));
}
