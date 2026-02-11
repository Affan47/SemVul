insertAt (unsigned int index_, const MSIndexVector & vect_)
{
  if (index_ == _pImpl->length())
    return append (vect_);


  if (_pImpl->insertAt (index_, *vect_._pImpl) == MSError::MSSuccess)
    changed();

  return *this;
}
