rnd_next(void)
{
  PFS_thread *pfs;

  for (m_pos.set_at(&m_next_pos);
       m_pos.m_index < thread_max;
       m_pos.next())
  {
    pfs= &thread_array[m_pos.m_index];
    if (pfs->m_lock.is_populated())
    {
      make_row(pfs);
      m_next_pos.set_after(&m_pos);
      return 0;
    }
  }

  return HA_ERR_END_OF_FILE;
}
