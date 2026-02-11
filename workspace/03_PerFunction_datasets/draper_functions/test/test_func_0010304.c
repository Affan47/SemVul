execute()
  {
    if (m_condition)
      cpu_dsPic->pc->jump(m_destination>>1);
    else
      cpu_dsPic->pc->increment();
  }
