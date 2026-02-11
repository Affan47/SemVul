resizePayload(Uint32 i)
{
  Uint32 requiredSize = payloadUsed+i;
  if (requiredSize < payloadAllocated) return;

  while (payloadAllocated < requiredSize) payloadAllocated += PAYLOAD_ALLOCATION_UNIT;
  unsigned char *newpayload = new unsigned char[payloadAllocated];
  OFBitmanipTemplate<unsigned char>::copyMem(payload, newpayload, payloadUsed);
  delete[] payload;
  payload = newpayload;
  return;
}
