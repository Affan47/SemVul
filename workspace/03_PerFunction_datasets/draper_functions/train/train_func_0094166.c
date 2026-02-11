ha_check(THD *thd, HA_CHECK_OPT *check_opt)
{
  int error;

  if ((table->s->mysql_version >= MYSQL_VERSION_ID) &&
      (check_opt->sql_flags & TT_FOR_UPGRADE))
    return 0;

  if (table->s->mysql_version < MYSQL_VERSION_ID)
  {
    if ((error= check_old_types()))
      return error;
    error= ha_check_for_upgrade(check_opt);
    if (error && (error != HA_ADMIN_NEEDS_CHECK))
      return error;
    if (!error && (check_opt->sql_flags & TT_FOR_UPGRADE))
      return 0;
  }
  if ((error= check(thd, check_opt)))
    return error;

  if (table->file != this)
    return error;
  return update_frm_version(table);
}
