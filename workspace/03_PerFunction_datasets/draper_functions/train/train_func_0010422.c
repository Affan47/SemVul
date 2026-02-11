setIOpin(PinModule *newPinModule)
{
  if (!m_sink) {
    m_sink = new RXSignalSink(this);
    m_PinModule = newPinModule;
    if (m_PinModule)
      m_PinModule->addSink(m_sink);
  }

}
