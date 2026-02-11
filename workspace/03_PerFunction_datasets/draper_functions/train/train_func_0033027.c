prepareToChangeWithoutCopy()
{
  if (_pOperations->refCount (_pElements) > 1)
    {
      _pOperations->deallocate (_pElements);
      _pElements = _pOperations->allocateWithSize (_pOperations->size (_pElements));
    }
}
