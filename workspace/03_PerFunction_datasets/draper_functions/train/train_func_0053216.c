ShortChecksum(u64 blocklength)
{
  u32 crc = CRCUpdateBlock(~0, (size_t)blocklength, outpointer);

  if (blocksize > blocklength)
  {
    crc = CRCUpdateBlock(crc, (size_t)(blocksize-blocklength));
  }

  crc ^= ~0;

  return crc;
}
