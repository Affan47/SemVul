sinc(float cutoff, float x, int N, struct FuncDef *window_func)
{

   float xx = x * cutoff;
   if (fabs(x)<1e-6)
      return cutoff;
   else if (fabs(x) > .5*N)
      return 0;

   return cutoff*sin(M_PI*xx)/(M_PI*xx) * compute_func(fabs(2.*x/N), window_func);
}
