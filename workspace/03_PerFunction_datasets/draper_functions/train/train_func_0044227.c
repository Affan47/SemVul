xgettimeofday (time_type *tv)
{
  time_type t;
  gettimeofday (&t, 0);
  if (timeval_subtract (0, 0, &t, &last_time))
    dmsg (D_TIMER,
	  "successive calls to gettimeofday() returned decreasing values");
  else
    last_time = t;
  *tv = last_time;
}
