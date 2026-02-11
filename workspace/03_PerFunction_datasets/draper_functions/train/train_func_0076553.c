syslinkSendPacket(SyslinkPacket *slp)
{
  int i = 0;
  int dataSize;
  uint8_t cksum[2] = {0};

  xSemaphoreTake(syslinkAccess, portMAX_DELAY);

  ASSERT(slp->length <= SYSLINK_MTU);

  sendBuffer[0] = SYSLINK_START_BYTE1;
  sendBuffer[1] = SYSLINK_START_BYTE2;
  sendBuffer[2] = slp->type;
  sendBuffer[3] = slp->length;

  memcpy(&sendBuffer[4], slp->data, slp->length);
  dataSize = slp->length + 6;

  for (i = 2; i < dataSize - 2; i++)
  {
    cksum[0] += sendBuffer[i];
    cksum[1] += cksum[0];
  }
  sendBuffer[dataSize-2] = cksum[0];
  sendBuffer[dataSize-1] = cksum[1];

  uartslkSendDataDmaBlocking(dataSize, sendBuffer);

  xSemaphoreGive(syslinkAccess);

  return 0;
}
