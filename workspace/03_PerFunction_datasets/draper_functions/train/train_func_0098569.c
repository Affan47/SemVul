log_in_use(const char* log_name)
{
  size_t log_name_len = strlen(log_name) + 1;
  THD *tmp;
  bool result = 0;
  DEBUG_SYNC(current_thd,"purge_logs_after_lock_index_before_thread_count");
  mysql_mutex_lock(&LOCK_thread_count);
  I_List_iterator<THD> it(threads);

  while ((tmp=it++))
  {
    LOG_INFO* linfo;
    if ((linfo = tmp->current_linfo))
    {
      mysql_mutex_lock(&linfo->lock);
      result = !memcmp(log_name, linfo->log_file_name, log_name_len);
      mysql_mutex_unlock(&linfo->lock);
      if (result)
	break;
    }
  }

  mysql_mutex_unlock(&LOCK_thread_count);
  return result;
}
