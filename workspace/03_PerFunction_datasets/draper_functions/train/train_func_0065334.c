rnd_next(void)
{
  PFS_thread *pfs_thread;
  PFS_events_waits *wait;

  for (m_pos.set_at(&m_next_pos);
       m_pos.m_index_1 < thread_max;
       m_pos.next_thread())
  {
    pfs_thread= &thread_array[m_pos.m_index_1];

    if (! pfs_thread->m_lock.is_populated())
    {

      continue;
    }


#define ONLY_SHOW_ONE_WAIT

#ifdef ONLY_SHOW_ONE_WAIT
    if (m_pos.m_index_2 >= 1)
      continue;
#else
    if (m_pos.m_index_2 >= pfs_thread->m_wait_locker_count)
      continue;
#endif

    wait= &pfs_thread->m_wait_locker_stack[m_pos.m_index_2].m_waits_current;

    if (wait->m_wait_class == NO_WAIT_CLASS)
    {


      continue;
    }

    make_row(true, pfs_thread, wait);

    m_next_pos.set_after(&m_pos);
    return 0;
  }

  return HA_ERR_END_OF_FILE;
}
