mysql_master_log_file_name(void)
{
  DBUG_ASSERT(active_mi && active_mi->rli.sql_thd == current_thd);
  return active_mi->rli.group_master_log_name;
}
