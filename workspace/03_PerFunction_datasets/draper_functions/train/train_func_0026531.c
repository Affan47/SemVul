unlock()
  {
    mysql_mutex_lock(&LOCK_delayed_insert);
    if (!--locks_in_memory)
    {
      mysql_mutex_lock(&mutex);
      if (thd.killed && ! stacked_inserts && ! tables_in_use)
      {
        mysql_cond_signal(&cond);
	status=1;
      }
      mysql_mutex_unlock(&mutex);
    }
    mysql_mutex_unlock(&LOCK_delayed_insert);
  }
