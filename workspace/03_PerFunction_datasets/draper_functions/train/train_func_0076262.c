XzBlock_Parse(CXzBlock *p, const Byte *header)
{
  unsigned pos;
  int numFilters, i;
  UInt32 headerSize = (UInt32)header[0] << 2;

  if (CrcCalc(header, headerSize) != GetUi32(header + headerSize))
    return SZ_ERROR_ARCHIVE;

  pos = 1;
  if (pos == headerSize)
    return SZ_ERROR_ARCHIVE;
  p->flags = header[pos++];

  if (XzBlock_HasPackSize(p))
  {
    READ_VARINT_AND_CHECK(header, pos, headerSize, &p->packSize);
    if (p->packSize == 0 || p->packSize + headerSize >= (UInt64)1 << 63)
      return SZ_ERROR_ARCHIVE;
  }

  if (XzBlock_HasUnpackSize(p))
    READ_VARINT_AND_CHECK(header, pos, headerSize, &p->unpackSize);

  numFilters = XzBlock_GetNumFilters(p);
  for (i = 0; i < numFilters; i++)
  {
    CXzFilter *filter = p->filters + i;
    UInt64 size;
    READ_VARINT_AND_CHECK(header, pos, headerSize, &filter->id);
    READ_VARINT_AND_CHECK(header, pos, headerSize, &size);
    if (size > headerSize - pos || size > XZ_FILTER_PROPS_SIZE_MAX)
      return SZ_ERROR_ARCHIVE;
    filter->propsSize = (UInt32)size;
    memcpy(filter->props, header + pos, (size_t)size);
    pos += (unsigned)size;

    #ifdef XZ_DUMP
    printf("\nf[%d] = %2X: ", i, filter->id);
    {
      int i;
      for (i = 0; i < size; i++)
        printf(" %2X", filter->props[i]);
    }
    #endif
  }

  while (pos < headerSize)
    if (header[pos++] != 0)
      return SZ_ERROR_ARCHIVE;
  return SZ_OK;
}
