HandleDeviceVendorCommandWithId(const cec_command &command)
{
  if (!m_processor->IsHandledByLibCEC(command.destination))
    return CEC_ABORT_REASON_INVALID_OPERAND;


  if (command.parameters[0] == 0x00 && command.parameters[1] == 0x00 && command.parameters[2] == 0xf0)
  {

    if (command.parameters[3] == 0x23)
    {
      cec_command response;
      cec_command::Format(response, command.destination, command.initiator, CEC_OPCODE_VENDOR_COMMAND_WITH_ID);


      response.parameters.PushBack(0x00); response.parameters.PushBack(0x00); response.parameters.PushBack(0xf0);


      response.parameters.PushBack(0x24);
      response.parameters.PushBack(0x00);
      response.parameters.PushBack(0x80);

      Transmit(response, false, true);
      return COMMAND_HANDLED;
    }
  }
  return CEC_ABORT_REASON_INVALID_OPERAND;
}
