TryLogicalAddress(cec_logical_address address, cec_version libCECSpecVersion )
{

  CCECBusDevice *device = m_busDevices->At(address);
  if (device)
  {

    if (device->IsPresent() || device->IsHandledByLibCEC())
      return false;


    return device->TryLogicalAddress(libCECSpecVersion);
  }

  return false;
}
