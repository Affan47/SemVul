Open(const char* file_name)
{
  unsigned char id;


  handle = imBinFileOpen(file_name);
  if (!handle)
    return IM_ERR_OPEN;

  imBinFileByteOrder(handle, IM_LITTLEENDIAN);


  imBinFileRead(handle, &id, 1, 1);
  if (imBinFileError(handle))
  {
    imBinFileClose(handle);
    return IM_ERR_ACCESS;
  }

  if (id != PCX_ID)
  {
    imBinFileClose(handle);
    return IM_ERR_FORMAT;
  }


  imBinFileRead(handle, &this->version, 1, 1);


  imBinFileRead(handle, &this->comp_type, 1, 1);
  if (this->comp_type)
    strcpy(this->compression, "RLE");
  else
    strcpy(this->compression, "NONE");

  this->image_count = 1;

  return IM_ERR_NONE;
}
