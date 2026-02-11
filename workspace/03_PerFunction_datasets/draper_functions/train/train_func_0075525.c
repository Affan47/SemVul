check_io_slave_killed(THD *thd, Master_info *mi, const char *info)
{
  if (io_slave_killed(thd, mi))
  {
    if (info && global_system_variables.log_warnings)
      sql_print_information("%s", info);
    return TRUE;
  }
  return FALSE;
}
