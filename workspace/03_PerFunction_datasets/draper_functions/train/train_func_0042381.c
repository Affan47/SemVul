timevar_get (timevar, elapsed)
     timevar_id_t timevar;
     struct timevar_time_def *elapsed;
{
  struct timevar_def *tv = &timevars[timevar];
  struct timevar_time_def now;

  *elapsed = tv->elapsed;


  if (tv->standalone)
    {
      get_time (&now);
      timevar_accumulate (elapsed, &tv->start_time, &now);
    }

  else if (stack->timevar == tv)
    {
      get_time (&now);
      timevar_accumulate (elapsed, &start_time, &now);
    }
}
