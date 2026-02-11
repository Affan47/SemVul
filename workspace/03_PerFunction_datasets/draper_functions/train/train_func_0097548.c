HandleSetStreamPath(const cec_command &command)
{
  if (!m_processor->CECInitialised())
    return CEC_ABORT_REASON_NOT_IN_CORRECT_MODE_TO_RESPOND;

  if (command.parameters.size >= 2)
  {
    uint16_t iStreamAddress = ((uint16_t)command.parameters[0] << 8) | ((uint16_t)command.parameters[1]);
    LIB_CEC->AddLog(CEC_LOG_DEBUG, ">> %s (%x) sets stream path to physical address %04x", ToString(command.initiator), command.initiator, iStreamAddress);


    CCECBusDevice *device = GetDeviceByPhysicalAddress(iStreamAddress);
    if (device)
    {
      if (device->IsHandledByLibCEC() && !device->IsActiveSource())
        device->ActivateSource();
      else
      {
        device->MarkAsActiveSource();
        device->TransmitActiveSource(true);
      }
      return COMMAND_HANDLED;
    }
  }

  return CEC_ABORT_REASON_INVALID_OPERAND;
}
