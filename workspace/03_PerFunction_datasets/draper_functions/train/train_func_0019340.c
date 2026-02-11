AllocateLogicalAddresses(CCECClient* client)
{
  libcec_configuration &configuration = *client->GetConfiguration();


  client->SetRegistered(false);


  CECDEVICEVEC devices;
  m_busDevices->GetByLogicalAddresses(devices, configuration.logicalAddresses);
  for (CECDEVICEVEC::const_iterator it = devices.begin(); it != devices.end(); it++)
  {

    CLockObject lock(m_mutex);
    m_clients.erase((*it)->GetLogicalAddress());
  }


  if (!client->AllocateLogicalAddresses())
  {
    m_libcec->AddLog(CEC_LOG_ERROR, "failed to find a free logical address for the client");
    return false;
  }


  devices.clear();
  m_busDevices->GetByLogicalAddresses(devices, configuration.logicalAddresses);
  for (CECDEVICEVEC::const_iterator it = devices.begin(); it != devices.end(); it++)
  {

    if (CLibCEC::IsValidPhysicalAddress(configuration.iPhysicalAddress))
      (*it)->SetPhysicalAddress(configuration.iPhysicalAddress);


    CLockObject lock(m_mutex);
    m_clients.erase((*it)->GetLogicalAddress());
    m_clients.insert(make_pair((*it)->GetLogicalAddress(), client));
  }


  SetLogicalAddresses(GetLogicalAddresses());


  m_bStallCommunication = false;

  return true;
}
