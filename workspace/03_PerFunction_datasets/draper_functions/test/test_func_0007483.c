HandleRequestActiveSource(const cec_command &command)
{
  if (m_processor->CECInitialised())
  {
    LIB_CEC->AddLog(CEC_LOG_DEBUG, ">> %i requests active source", (uint8_t) command.initiator);
    m_processor->GetDevice(command.initiator)->SetPowerStatus(CEC_POWER_STATUS_ON);

    vector<CCECBusDevice *> devices;
    for (size_t iDevicePtr = 0; iDevicePtr < GetMyDevices(devices); iDevicePtr++)
      devices[iDevicePtr]->TransmitActiveSource(true);
  }

  return COMMAND_HANDLED;
}
