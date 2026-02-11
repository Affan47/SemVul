ParseSocketLink(Packet *buffer, SocketLink **sl)
{
  if(!sl)
    return 0;

  unsigned int handle;

  if(buffer->DecodeUInt32(handle)) {

    unsigned int index    = handle & 0xffff;

    *sl = links[index&0x0f];
    if( (*sl) && (*sl)->getHandle() != handle)
      *sl = 0;

    return true;
  }

  return false;

}
