init(void *owner,
                         Uint32 fieldLength,
                         Uint32 bytesTransferred,
                         E_ByteOrder byteOrder)
{
  if (! buf_)
  {
    capacity_ = DcmWriteCacheBufsize;
    buf_ = new Uint8[capacity_];
  }

  if (owner != owner_)
  {
    owner_ = owner;
    fieldLength_ = fieldLength;
    fieldOffset_ = bytesTransferred;
    byteOrder_ = byteOrder;
    offset_ = 0;
    numBytes_ = 0;
  }
}
