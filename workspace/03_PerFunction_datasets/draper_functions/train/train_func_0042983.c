ActivateSource(bool bTransmitDelayedCommandsOnly )
{

  CCECBusDevice* tv = m_processor->GetDevice(CECDEVICE_TV);
  if (m_busDevice->IsActiveSource() &&
      m_busDevice->IsHandledByLibCEC() &&
      tv && tv->GetCurrentPowerStatus() != CEC_POWER_STATUS_ON &&
      !bTransmitDelayedCommandsOnly)
  {

    if (m_imageViewOnCheck && !m_imageViewOnCheck->IsRunning())
      return m_imageViewOnCheck->CreateThread(false);
  }

  return CCECCommandHandler::ActivateSource(bTransmitDelayedCommandsOnly);
}
