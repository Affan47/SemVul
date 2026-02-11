NextFrame()
{
  if (curFrame < numFrames - 1)
  {
    ++curFrame;
    return true;
  }

  return false;
}
