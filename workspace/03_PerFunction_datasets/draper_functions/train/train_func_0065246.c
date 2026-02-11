HandleVendorCommandSLInit(const cec_command &command)
{
  CCECBusDevice* dev = m_processor->GetDevice(command.destination);
  if (dev && dev->IsHandledByLibCEC())
  {
    if (!dev->IsActiveSource())
    {
      dev->SetPowerStatus(CEC_POWER_STATUS_STANDBY);
      dev->TransmitPowerState(command.initiator, true);
    }

    TransmitVendorCommandSLAckInit(command.destination, command.initiator);
  }
}
