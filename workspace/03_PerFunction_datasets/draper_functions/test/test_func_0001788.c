sanityCheck( int line, char *file, const char *func, double v, double diff, double dt, JT a, JT b, JT c, JT d )
{
   if ( v > 100.0 ) {
      err_msg( "file %s, line %d, fn %s: val > 100: %g ~ %g / %g = (%llu - %llu) / (%llu - %llu)\n", file, line, func, v, diff, dt, a, b, c, d );
      return 100.0;
   }
   else if ( v < 0.0 ) {
      err_msg( "file %s, line %d, fn %s: val < 0: %g ~ %g / %g = (%llu - %llu) / (%llu - %llu)\n", file, line, func, v, diff, dt, a, b, c, d );
      return 0.0;
   }
   return v;
}
