send(const MSString& aString_)
{
  if (isSet(MSProtocolConnection<MSString>::Reset)==MSTrue) return MSFalse;
  if (readChannel()==0) return MSFalse;

  MSBuffer *pBuffer=new MSBuffer;
  pBuffer->stuff(aString_.string(),aString_.length());
  sendTheBuffer(pBuffer);
  if (isSet(MSProtocolConnection<MSString>::WritePause)==MSFalse) writeChannel()->enable();

  return doWrite(MSFalse);
}
