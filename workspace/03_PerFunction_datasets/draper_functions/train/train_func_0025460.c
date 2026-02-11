operator+= (const unsigned int value_)
{
  unsigned int len=_pImpl->length();

  if (len>0)
    {
      unsigned int *pData=data();
      _pImpl->prepareToChangeWithoutCopy();

      if (pData==data())
	{
	  while (len--)
	    {
	      *pData++ += value_;
	    }
	}
      else
	{

	  unsigned int *pNewData=data();

	  while (len--)
	    {
	      *pNewData++ = *pData++ + value_;
	    }
	}

      changed();
    }

  return *this;
}
