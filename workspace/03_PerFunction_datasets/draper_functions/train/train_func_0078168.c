parse_daystart (const struct parser_table* entry, char **argv, int *arg_ptr)
{
  struct tm *local;

  (void) entry;
  (void) argv;
  (void) arg_ptr;

  if (options.full_days == false)
    {
      options.cur_day_start.tv_sec += DAYSECS;
      options.cur_day_start.tv_nsec = 0;
      local = localtime (&options.cur_day_start.tv_sec);
      options.cur_day_start.tv_sec -= (local
				       ? (local->tm_sec + local->tm_min * 60
					  + local->tm_hour * 3600)
				       : options.cur_day_start.tv_sec % DAYSECS);
      options.full_days = true;
    }
  return true;
}
