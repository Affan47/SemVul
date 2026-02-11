Write(const void *data, UInt32 size, UInt32 *processedSize)
{
  UInt32 i;
  for (i = 0; i < size && Pos < BufferSize; i++)
    Buffer[Pos++] = ((const Byte *)data)[i];
  if(processedSize != NULL)
    *processedSize = i;
  if (i != size)
  {
    fprintf(_f, "\nERROR: Buffer is full\n");
    return E_FAIL;
  }
  return S_OK;
}
