getMapId(ArMapId *mapIdOut,
                                     bool isInternalCall)
{
  if (isInternalCall) {
    lock();
  }
  bool isSuccess = myCurrentMap->getMapId(mapIdOut, true);
  if (isInternalCall) {
    unlock();
  }
  return isSuccess;
}
