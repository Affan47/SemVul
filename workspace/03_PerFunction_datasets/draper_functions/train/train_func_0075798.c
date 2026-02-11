commanderCacheSelectorUpdate(void)
{
  uint32_t tickNow = xTaskGetTickCount();


  if ((tickNow - extrxCache.timestamp) < COMMANDER_WDT_TIMEOUT_STABILIZE) {
    activeCache = &extrxCache;
  } else if ((tickNow - crtpCache.timestamp) < COMMANDER_WDT_TIMEOUT_STABILIZE) {
    activeCache = &crtpCache;
  } else if ((tickNow - extrxCache.timestamp) < COMMANDER_WDT_TIMEOUT_SHUTDOWN) {
    activeCache = &extrxCache;
    commanderLevelRPY();
  } else if ((tickNow - crtpCache.timestamp) < COMMANDER_WDT_TIMEOUT_SHUTDOWN) {
    activeCache = &crtpCache;
    commanderLevelRPY();
  } else {
    activeCache = &crtpCache;
    commanderDropToGround();
  }
}
