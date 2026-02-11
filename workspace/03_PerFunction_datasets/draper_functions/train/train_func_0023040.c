reset(void)
{
  myDataMutex.lock();
  while (myTimes.size() > 0)
    myTimes.pop_back();
  while (myPoses.size() > 0)
    myPoses.pop_back();
  myDataMutex.unlock();
}
