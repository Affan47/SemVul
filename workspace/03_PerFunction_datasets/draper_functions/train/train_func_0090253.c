end_file_wait_v1(PSI_file_locker *locker,
                             size_t count)
{
  PFS_wait_locker *pfs_locker= reinterpret_cast<PFS_wait_locker*> (locker);
  DBUG_ASSERT(pfs_locker != NULL);
  PFS_events_waits *wait= &pfs_locker->m_waits_current;

  wait->m_number_of_bytes= count;
  if (wait->m_timer_state == TIMER_STATE_STARTED)
  {
    wait->m_timer_end= get_timer_value(pfs_locker->m_timer_name);
    wait->m_timer_state= TIMER_STATE_TIMED;
  }
  if (flag_events_waits_history)
    insert_events_waits_history(wait->m_thread, wait);
  if (flag_events_waits_history_long)
    insert_events_waits_history_long(wait);

  PFS_file *file= pfs_locker->m_target.m_file;
  PFS_single_stat_chain *stat= find_per_thread_file_class_wait_stat(wait->m_thread, file->m_class);


  if (wait->m_timer_state == TIMER_STATE_TIMED)
  {
    ulonglong wait_time= wait->m_timer_end - wait->m_timer_start;
    aggregate_single_stat_chain(&file->m_wait_stat, wait_time);
    aggregate_single_stat_chain(stat, wait_time);
  }
  else
  {
    increment_single_stat_chain(&file->m_wait_stat);
    increment_single_stat_chain(stat);
  }

  PFS_file_class *klass= file->m_class;

  switch(wait->m_operation)
  {
  case OPERATION_TYPE_FILEREAD:
    file->m_file_stat.m_count_read++;
    file->m_file_stat.m_read_bytes+= count;
    klass->m_file_stat.m_count_read++;
    klass->m_file_stat.m_read_bytes+= count;
    break;
  case OPERATION_TYPE_FILEWRITE:
    file->m_file_stat.m_count_write++;
    file->m_file_stat.m_write_bytes+= count;
    klass->m_file_stat.m_count_write++;
    klass->m_file_stat.m_write_bytes+= count;
    break;
  case OPERATION_TYPE_FILECLOSE:
  case OPERATION_TYPE_FILESTREAMCLOSE:
  case OPERATION_TYPE_FILESTAT:
    release_file(pfs_locker->m_target.m_file);
    break;
  case OPERATION_TYPE_FILEDELETE:
    destroy_file(wait->m_thread, pfs_locker->m_target.m_file);
    break;
  default:
    break;
  }

  wait->m_thread->m_wait_locker_count--;
}
