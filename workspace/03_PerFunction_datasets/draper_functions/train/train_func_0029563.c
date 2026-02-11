xsh_util_get_infsup(double* piw,
                    double w,
                    int i_start,
                    int i_end,
                    int* i_inf,
                    int* i_sup)
{

   int i=0;
   for(i = i_start;i < i_end;i++) {
      if (piw[i] < w) {
         *i_inf=i;
         *i_sup=i+1;
      }
   }

   return cpl_error_get_code();
}
