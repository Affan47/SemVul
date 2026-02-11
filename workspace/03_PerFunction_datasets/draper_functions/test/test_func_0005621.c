thd_wait_begin(MYSQL_THD thd, int wait_type)
{
  MYSQL_CALLBACK(thread_scheduler, thd_wait_begin, (thd, wait_type));
}
