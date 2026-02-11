commanderCrtpCB(CRTPPacket* pk)
{
  crtpCache.targetVal[!crtpCache.activeSide] = *((struct CommanderCrtpValues*)pk->data);
  crtpCache.activeSide = !crtpCache.activeSide;
  crtpCache.timestamp = xTaskGetTickCount();

  if (crtpCache.targetVal[crtpCache.activeSide].thrust == 0) {
    thrustLocked = false;
  }
}
