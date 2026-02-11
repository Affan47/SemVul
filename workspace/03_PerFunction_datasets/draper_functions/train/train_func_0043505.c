select (const MSVectorImpl & vImpl_, const MSIndexVector & iVect_)
{
  if (this == &vImpl_)
    {
      select (iVect_);
      return;
    }

  _pOperations->deallocate (_pElements, _len);
  _len = iVect_.length();
  _pElements = _pOperations->allocate (_len);

  if (_len)
    {
      unsigned int *pIndices = iVect_.data();

      for (unsigned int i=0; i<_len; i++)
	_pOperations->set (_pElements, i, vImpl_.internalGet (pIndices[i]), MSRaw);
    }
}
