unlock(void)
{
  DBUG_ENTER("Query_cache::unlock");
  mysql_mutex_lock(&structure_guard_mutex);
#ifndef DBUG_OFF
  THD *thd= current_thd;
  if (thd)
    DBUG_ASSERT(m_cache_lock_thread_id == thd->thread_id);
#endif
  DBUG_ASSERT(m_cache_lock_status == Query_cache::LOCKED ||
              m_cache_lock_status == Query_cache::LOCKED_NO_WAIT);
  m_cache_lock_status= Query_cache::UNLOCKED;
  DBUG_PRINT("Query_cache",("Sending signal"));
  mysql_cond_signal(&COND_cache_status_changed);
  mysql_mutex_unlock(&structure_guard_mutex);
  DBUG_VOID_RETURN;
}
