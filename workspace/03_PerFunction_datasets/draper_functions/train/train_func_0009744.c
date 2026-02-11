HandleFeatureAbort(const cec_command &command)
{
  CCECBusDevice* primary = m_processor->GetPrimaryDevice();
  if (command.parameters.size == 0 && primary->GetLogicalAddress() != CECDEVICE_UNKNOWN &&
      primary->GetCurrentPowerStatus() == CEC_POWER_STATUS_ON && !SLInitialised() &&
      command.initiator == CECDEVICE_TV)
  {
    if (!SLInitialised() && m_processor->IsActiveSource(command.destination))
    {
      TransmitVendorCommandSLAckInit(command.destination, command.initiator);
      return COMMAND_HANDLED;
    }
  }

  return CCECCommandHandler::HandleFeatureAbort(command);
}
