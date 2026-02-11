append (const MSVectorImpl & vImpl_)
{
  if (vImpl_._len > 0)
    {
      reallocateAndCopy(_len + vImpl_._len);
      _pOperations->copy (vImpl_._pElements, _pElements, vImpl_._len, 0, _len, MSRaw);
      _len += vImpl_._len;

      return MSError::MSSuccess;
    }

  return MSError::MSFailure;
}
