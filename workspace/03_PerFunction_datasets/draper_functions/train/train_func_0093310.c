newFactory() const
{
  DcmInputStreamFactory *result = NULL;
  if (currentProducer() == &producer_)
  {

    result = new DcmInputFileStreamFactory(filename_, tell());
  }
  return result;
}
