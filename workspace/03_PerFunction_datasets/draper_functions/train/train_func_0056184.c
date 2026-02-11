vec3_cmpV( const double u[3], const double v[3], double precision )
{
   int ret, i;
   ret = 0;
   for (i=0; i<3; i++)
      if (fabs(u[i]-v[i]) > precision)
         ret = ret + 1;
   return ret;
}
