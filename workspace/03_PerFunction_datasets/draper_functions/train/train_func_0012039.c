net_store_length(uchar *packet, ulonglong length)
{
  if (length < (ulonglong) LL(251))
  {
    *packet=(uchar) length;
    return packet+1;
  }

  if (length < (ulonglong) LL(65536))
  {
    *packet++=252;
    int2store(packet,(uint) length);
    return packet+2;
  }
  if (length < (ulonglong) LL(16777216))
  {
    *packet++=253;
    int3store(packet,(ulong) length);
    return packet+3;
  }
  *packet++=254;
  int8store(packet,length);
  return packet+8;
}
