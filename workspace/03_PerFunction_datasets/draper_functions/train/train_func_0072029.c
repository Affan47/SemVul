start_table_wait_v1(PSI_table_locker* locker,
                                const char *src_file, uint src_line)
{
  PFS_wait_locker *pfs_locker= reinterpret_cast<PFS_wait_locker*> (locker);
  DBUG_ASSERT(pfs_locker != NULL);

  PFS_events_waits *wait= &pfs_locker->m_waits_current;
  if (wait->m_timer_state == TIMER_STATE_STARTING)
  {
    wait->m_timer_start= get_timer_value(pfs_locker->m_timer_name);
    wait->m_timer_state= TIMER_STATE_STARTED;
  }
  wait->m_source_file= src_file;
  wait->m_source_line= src_line;
  wait->m_operation= OPERATION_TYPE_LOCK;
  PFS_table_share *share= pfs_locker->m_target.m_table->m_share;
  wait->m_schema_name= share->m_schema_name;
  wait->m_schema_name_length= share->m_schema_name_length;
  wait->m_object_name= share->m_table_name;
  wait->m_object_name_length= share->m_table_name_length;
}
