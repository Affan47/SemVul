iKRNReadDescription(imBinFile* handle, char* comment, int *size)
{
  imbyte byte_value = 0;


  while(byte_value != '\n')
  {
    imBinFileRead(handle, &byte_value, 1, 1);
    if (imBinFileError(handle))
      return 0;
  }

  *size = 0;


  imBinFileRead(handle, &byte_value, 1, 1);
  if (imBinFileError(handle))
    return 0;

  while(byte_value != '\n')
  {
    if (byte_value != '\r')
    {
      comment[*size] = byte_value;
      (*size)++;
    }

    imBinFileRead(handle, &byte_value, 1, 1);
    if (imBinFileError(handle))
      return 0;
  }

  if (*size != 0)
  {
    comment[*size] = 0;
    (*size)++;
  }

  return 1;
}
