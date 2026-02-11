writeFile(const char *fileName,
                                     bool internalCall,
                                     unsigned char *md5DigestBuffer,
                                     size_t md5DigestBufferLen,
                                     time_t fileTimestamp)
{
  if (!internalCall) {
    ArLog::log(ArLog::Normal,
	       "ArMap::writeFile(%s) about to lock",
	       fileName);
    lock();
    ArLog::log(ArLog::Normal,
	       "ArMap::writeFile(%s) locked",
	       fileName);

  }

  bool isSuccess = myCurrentMap->writeFile(fileName,
                                           true,
                                           md5DigestBuffer,
                                           md5DigestBufferLen,
                                           fileTimestamp);

  if (isSuccess) {
    myReadFileStat = myCurrentMap->getReadFileStat();
  }

  if (!internalCall)
    unlock();
  return true;

}
