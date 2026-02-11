read(unsigned long maxTime)
{
  if (!myDevice) return ReadError;
  ArTime startTime;
  startTime.setToNow();
  int result = 0;
  while(maxTime == 0 || startTime.mSecSince() < (long)maxTime)
  {
    result |= myNMEAParser.parse(myDevice);
    if(result & ReadError || result & ReadFinished)
    {
#ifdef DEBUG_ARGPS
      std::cerr << "ArGPS: finished reading all available data (or error reading).\n";
#endif
      return result;
    }
  }
#ifdef DEBUG_ARGPS
  if(maxTime != 0)
    fprintf(stderr, "ArGPS::read() reached maxTime %lu (time=%lu), returning.\n", maxTime, startTime.mSecSince());
#endif

  return result;
}
