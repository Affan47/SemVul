selectiveAssign (const MSBinaryVector & bVect_, const unsigned int value_)
{
  if (doChanged() == MSTrue)
    changed (_pImpl->setIndexSelected (bVect_, (void *)&value_));
  else
    _pImpl->setSelected (bVect_, (void *)&value_);

  return *this;
}
