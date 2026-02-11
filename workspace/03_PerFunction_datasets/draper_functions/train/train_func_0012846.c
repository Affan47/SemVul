s48_enter_time(s48_call_t call, struct timeval *now)
{
  s48_ref_t	sch_time;

  sch_time = s48_make_record_2(call, time_type_binding);

  s48_unsafe_record_set_2(call, sch_time, 0, s48_enter_long_2(call, now->tv_sec));
  s48_unsafe_record_set_2(call, sch_time, 1, s48_enter_long_2(call, now->tv_usec));

  return sch_time;
}
