_k_slotProgress()
{
  const int p = m_parent->value();
  if (p == 18)
  {
     m_parent->reset();
     m_parent->setValue(1);
     m_timeStep = m_timeStep * 2;
     m_timer.start(m_timeStep);
  }
  else
  {
     m_parent->setValue(p+1);
  }
}
