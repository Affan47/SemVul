flush()
{

  if (opt_log)
    mysql_log.reopen_file();
  if (opt_slow_log)
    mysql_slow_log.reopen_file();
}
