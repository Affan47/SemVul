drop (int numEls_)
{
  if (numEls_ == 0)
    return MSError::MSFailure;

  unsigned int numDoomed = MSUtil::abs (numEls_);

  if (numDoomed >= _len)
    removeAll();
  else
    {
      if (numEls_ > 0)
	removeAt (0, numDoomed);
      else
	removeAt (_len-numDoomed, numDoomed);
    }

  return MSError::MSSuccess;
}
