GetDeviceOSDName(const cec_logical_address iAddress)
{
  cec_osd_name retVal;
  retVal.device = iAddress;
  retVal.name[0] = 0;

  CCECBusDevice *device = m_processor->GetDevice(iAddress);
  if (device)
  {
    CStdString strOSDName = device->GetOSDName(GetPrimaryLogicalAdddress());
    snprintf(retVal.name, sizeof(retVal.name), "%s", strOSDName.c_str());
    retVal.device = iAddress;
  }

  return retVal;
}
