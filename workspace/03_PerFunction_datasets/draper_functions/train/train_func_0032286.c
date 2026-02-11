m2(void)
{
  char mark1[32], mark2[32];
  double dt1, dt2, dt0;
  int i;

  dt0 = 1.0;
  for ( i = 0; i < ntests; i++ )
    {
      set_time_mark(mark2);
      set_time_mark(mark1);
      dt1 = get_time_val(mark1);
      dt2 = get_time_val(mark2);
      if ( dt2 < dt0 ) dt0 = dt2;
      if ( dt2 < dt1 ) fprintf(rt_unit, "estimate_overhead: internal error\n");
    }

  return (dt0);
}
