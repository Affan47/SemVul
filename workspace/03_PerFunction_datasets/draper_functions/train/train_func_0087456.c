InitHandler(void)
{
  CCECBusDevice *primary = m_processor->GetPrimaryDevice();
  if (primary && primary->GetLogicalAddress() != CECDEVICE_UNREGISTERED)
  {

    if (m_busDevice->GetLogicalAddress() == CECDEVICE_TV &&
        primary && m_busDevice->GetLogicalAddress() != primary->GetLogicalAddress())
    {
      primary->SetVendorId(CEC_VENDOR_PHILIPS);
      primary->ReplaceHandler(false);
    }
  }

  return CCECCommandHandler::InitHandler();
}
