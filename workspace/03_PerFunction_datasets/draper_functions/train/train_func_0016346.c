close_active_mi()
{
  mysql_mutex_lock(&LOCK_active_mi);
  if (active_mi)
  {
    end_master_info(active_mi);
    delete active_mi;
    active_mi= 0;
  }
  mysql_mutex_unlock(&LOCK_active_mi);
}
