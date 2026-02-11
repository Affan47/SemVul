Lzma2Dec_GetOldProps(Byte prop, Byte *props)
{
  UInt32 dicSize;
  if (prop > 40)
    return SZ_ERROR_UNSUPPORTED;
  dicSize = (prop == 40) ? 0xFFFFFFFF : LZMA2_DIC_SIZE_FROM_PROP(prop);
  props[0] = (Byte)LZMA2_LCLP_MAX;
  props[1] = (Byte)(dicSize);
  props[2] = (Byte)(dicSize >> 8);
  props[3] = (Byte)(dicSize >> 16);
  props[4] = (Byte)(dicSize >> 24);
  return SZ_OK;
}
