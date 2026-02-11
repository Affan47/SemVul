thd_enter_cond(MYSQL_THD thd, mysql_cond_t *cond,
                           mysql_mutex_t *mutex, const char *msg)
{
  if (!thd)
    thd= current_thd;

  return thd->enter_cond(cond, mutex, msg);
}
