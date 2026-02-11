my_timer_reset(my_timer_t *timer, int *state)
{
  int status;
  struct itimerspec old_spec;


  const struct timespec zero_time= { .tv_sec= 0, .tv_nsec= 0 };
  const struct itimerspec zero_spec= { .it_value= zero_time };


  if (! (status= timer_settime(timer->id, 0, &zero_spec, &old_spec)))
    *state= (old_spec.it_value.tv_sec || old_spec.it_value.tv_nsec);

  return status;
}
