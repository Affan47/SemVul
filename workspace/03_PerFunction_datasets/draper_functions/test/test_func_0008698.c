HandleSetMenuLanguage(const cec_command &command)
{
  if (command.parameters.size == 3)
  {
    CCECBusDevice *device = GetDevice(command.initiator);
    if (device)
    {
      cec_menu_language language;
      language.device = command.initiator;
      for (uint8_t iPtr = 0; iPtr < 4; iPtr++)
        language.language[iPtr] = command.parameters[iPtr];
      language.language[3] = 0;
      device->SetMenuLanguage(language);
      return COMMAND_HANDLED;
    }
  }

  return CEC_ABORT_REASON_INVALID_OPERAND;
}
