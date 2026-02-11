extractStringFromPayload(OFString& str)
{
  Uint32 length = 0;
  if (! extractIntFromPayload(length)) return OFFalse;

  if (payloadReadOffset + length > payloadUsed) return OFFalse;

  str = (const char *)(payload+payloadReadOffset);
  payloadReadOffset += length;
  return OFTrue;
}
