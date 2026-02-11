HandleDeviceCecVersion(const cec_command &command)
{
  if (command.parameters.size == 1)
  {
    CCECBusDevice *device = GetDevice(command.initiator);
    if (device)
      device->SetCecVersion((cec_version) command.parameters[0]);

    return COMMAND_HANDLED;
  }

  return CEC_ABORT_REASON_INVALID_OPERAND;
}
