ReadFromDevice(uint32_t iTimeout, size_t iSize )
{
  ssize_t iBytesRead(0);
  uint8_t buff[256];
  if (iSize > 256)
    iSize = 256;


  {
    CLockObject lock(m_mutex);
    if (!IsOpen())
      return false;

    do {

      iBytesRead = m_port->Read(buff, sizeof(uint8_t) * iSize, iTimeout);
    } while(m_port->GetErrorNumber() == EINTR);


    if (m_port->GetErrorNumber())
    {
      LIB_CEC->AddLog(CEC_LOG_ERROR, "error reading from serial port: %s", m_port->GetError().c_str());

      return false;
    }
  }

  if (iBytesRead < 0 || iBytesRead > 256)
    return false;
  else if (iBytesRead > 0)
  {

    m_adapterMessageQueue->AddData(buff, iBytesRead);
  }

  return true;
}
