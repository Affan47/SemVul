clearAnimation(bool restartTime)
{
  qDeleteAll(mAnimList);
  mAnimList.clear();


  if (restartTime)
  {
    mTime.restart();
    mDeltaT = 0;
    mDelayT = 0;
  }
  mStartAnimation = true;
}
