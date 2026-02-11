consolePutchar(int ch)
{
  int i;
  bool isInInterrupt = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;

  if (!isInit) {
    return 0;
  }

  if (isInInterrupt) {
    return consolePutcharFromISR(ch);
  }

  if (xSemaphoreTake(synch, portMAX_DELAY) == pdTRUE)
  {
    if (messageToPrint.size < CRTP_MAX_DATA_SIZE)
    {
      messageToPrint.data[messageToPrint.size] = (unsigned char)ch;
      messageToPrint.size++;
    }
    if (ch == '\n' || messageToPrint.size >= CRTP_MAX_DATA_SIZE)
    {
      if (crtpGetFreeTxQueuePackets() == 1)
      {
        for (i = 0; i < sizeof(fullMsg) && (messageToPrint.size - i) > 0; i++)
        {
          messageToPrint.data[messageToPrint.size - i] =
              (uint8_t)fullMsg[sizeof(fullMsg) - i - 1];
        }
      }
      consoleSendMessage();
    }
    xSemaphoreGive(synch);
  }

  return (unsigned char)ch;
}
