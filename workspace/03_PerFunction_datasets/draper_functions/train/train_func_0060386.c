log_slow(THD *thd, time_t current_time, time_t query_start_arg,
           const char *user_host, uint user_host_len,
           ulonglong query_utime, ulonglong lock_utime, bool is_command,
           const char *sql_text, uint sql_text_len)
{
  Silence_log_table_errors error_handler;
  thd->push_internal_handler(&error_handler);
  bool retval= mysql_slow_log.write(thd, current_time, query_start_arg,
                                    user_host, user_host_len,
                                    query_utime, lock_utime, is_command,
                                    sql_text, sql_text_len);
  thd->pop_internal_handler();
  return retval;
}
