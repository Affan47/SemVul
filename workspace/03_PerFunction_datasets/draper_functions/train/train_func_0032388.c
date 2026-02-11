GetDevicePowerStatus(const cec_logical_address iAddress)
{
  CCECBusDevice *device = m_processor->GetDevice(iAddress);
  if (device)
    return device->GetPowerStatus(GetPrimaryLogicalAdddress());
  return CEC_POWER_STATUS_UNKNOWN;
}
