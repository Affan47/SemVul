hasBordersOrShading(void) const
{
  if(getBlock() && (getBlock()->hasBorders() || (getBlock()->getPattern() > 0)))
  {
    return true;
  }
  return false;
}
