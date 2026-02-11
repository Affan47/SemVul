iGIFSkipSubBlocks(imBinFile* handle)
{
  unsigned char byte_value;
  do
  {

    imBinFileRead(handle, &byte_value, 1, 1);

    if (imBinFileError(handle))
      return IM_ERR_ACCESS;


    if (byte_value) imBinFileSeekOffset(handle, byte_value);
  }while (byte_value != 0);

  return IM_ERR_NONE;
}
