create_iopin_map()
{
  package = new Package(16);

  package->assign_pin( 1, m_Q[1]);
  package->assign_pin( 2, m_Q[2]);
  package->assign_pin( 3, m_Q[3]);
  package->assign_pin( 4, m_Q[4]);
  package->assign_pin( 5, m_Q[5]);
  package->assign_pin( 6, m_Q[6]);
  package->assign_pin( 7, m_Q[7]);
  package->assign_pin( 9, m_Qs);
  package->assign_pin(10, m_reset);
  package->assign_pin(11, m_clock);
  package->assign_pin(12, m_strobe);
  package->assign_pin(13, m_enable);
  package->assign_pin(14, m_Ds);
  package->assign_pin(15, m_Q[0]);

}
