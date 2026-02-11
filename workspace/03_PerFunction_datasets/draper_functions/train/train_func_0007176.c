GetConfiguration(libcec_configuration &configuration)
{

  if (!RequestSettings())
    return false;


  configuration.iFirmwareVersion = m_persistedConfiguration.iFirmwareVersion;
  configuration.deviceTypes      = m_persistedConfiguration.deviceTypes;
  configuration.iPhysicalAddress = m_persistedConfiguration.iPhysicalAddress;
  snprintf(configuration.strDeviceName, 13, "%s", m_persistedConfiguration.strDeviceName);

  return true;
}
