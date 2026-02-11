timeReached(double timeLimit)
{
  if(1.0*clock()/CLOCKS_PER_SEC >= timeLimit)
    return true;
  else
    return false;
}
