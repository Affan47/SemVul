platformCommandProcess(uint8_t command, uint8_t *data)
{
  SyslinkPacket slp;

  switch (command) {
    case setContinousWave:
      slp.type = SYSLINK_RADIO_CONTWAVE;
      slp.length = 1;
      slp.data[0] = data[0];
      syslinkSendPacket(&slp);
      break;
    default:
      break;
  }
}
