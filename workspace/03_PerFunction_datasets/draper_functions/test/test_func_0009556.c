operator- (const MSIndexVector & vect_, const unsigned int value_)
{
  unsigned int len=vect_._pImpl->length();
  MSBuiltinVectorImpl *pResImpl = (MSBuiltinVectorImpl *)vect_._pImpl->create(len,vect_.vectorData()->size());
  unsigned int *pData=vect_.data(), *pResData=((MSIndexVector::Data *)pResImpl->data())->elements();

  while (len--)
    {
      *pResData++ = *pData++ - value_;
    }

  return MSIndexVector(pResImpl);
}
