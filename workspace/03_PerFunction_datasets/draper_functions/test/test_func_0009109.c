setIOpin(PinModule *p1, PinModule *p2, PinModule *p3, PinModule *p4)
{
  Dprintf(("%s::setIOpin %s\n", name().c_str(), (p1 && &(p1->getPin())) ? p1->getPin().name().c_str():"unknown"));
  if (!&(p1->getPin()))
  {
	Dprintf(("FIXME %s::setIOpin called where p1 has unassigned pin\n", name().c_str()));
	return;
  }

  setIOPin1(p1);
  setIOPin2(p2);
  if (p3)
  {
    m_PinModule[2] = p3;
    if (!m_source[2])
        m_source[2] = new CCPSignalSource(this, 2);
  }
  else
  {
	if (m_source[2])
	{
		delete m_source[2];
		m_source[2] = 0;
	}
	m_PinModule[2] = 0;
  }
  if (p4)
  {
    m_PinModule[3] = p4;
    if (!m_source[3])
        m_source[3] = new CCPSignalSource(this, 3);
  }
  else
  {
	if (m_source[3])
	{
		delete m_source[3];
		m_source[3] = 0;
	}
  }

}
