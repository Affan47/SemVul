HandleVendorRemoteButtonDown(const cec_command &command)
{
  if (command.parameters.size == 0)
    return CEC_ABORT_REASON_INVALID_OPERAND;

  if (!m_processor->CECInitialised())
    return CEC_ABORT_REASON_NOT_IN_CORRECT_MODE_TO_RESPOND;

  CCECClient *client = m_processor->GetClient(command.destination);
  if (!client)
    return CEC_ABORT_REASON_NOT_IN_CORRECT_MODE_TO_RESPOND;

  cec_keypress key;
  key.duration = CEC_BUTTON_TIMEOUT;
  key.keycode = (cec_user_control_code)command.parameters[0];

  if (client)
    client->AddKey(key);

  return COMMAND_HANDLED;
}
