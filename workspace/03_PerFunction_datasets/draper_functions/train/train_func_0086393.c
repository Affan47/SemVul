iRASDecodeScanLine(imBinFile* handle, unsigned char* DecodedBuffer, int BufferSize)
{
  int index = 0;
  unsigned char count = 0;
  unsigned char value = 0;

  while (index < BufferSize)
  {
    imBinFileRead(handle, &value, 1, 1);

    if (value == RAS_ESCAPE)
    {
      imBinFileRead(handle, &count, 1, 1);

      if (count != 0)
      {
        imBinFileRead(handle, &value, 1, 1);

        count++;
        while (count-- && index < BufferSize)
        {
          *DecodedBuffer++ = value;
          index++;
        }
      }
      else
      {
        *DecodedBuffer++ = RAS_ESCAPE;
        index++;
      }
    }
    else
    {
      *DecodedBuffer++ = value;
      index++;
    }

    if (imBinFileError(handle))
      return IM_ERR_ACCESS;
  }

  return IM_ERR_NONE;
}
