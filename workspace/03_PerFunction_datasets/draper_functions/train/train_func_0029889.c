getStartingArguments(void) const
{
  if (myUsingBuilder)
    return myBuilder->getFullString();
  else
    return NULL;
}
