IsPresentDeviceType(cec_device_type type)
{
  CECDEVICEVEC devices;
  m_busDevices->GetByType(type, devices);
  CCECDeviceMap::FilterActive(devices);
  return !devices.empty();
}
