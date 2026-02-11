setup_connection_thread_globals(THD *thd)
{
  if (thd->store_globals())
  {
    close_connection(thd, ER_OUT_OF_RESOURCES);
    statistic_increment(aborted_connects,&LOCK_status);
    MYSQL_CALLBACK(thread_scheduler, end_thread, (thd, 0));
    return 1;
  }
  return 0;
}
