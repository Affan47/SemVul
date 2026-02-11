New(const char* file_name)
{
  this->tiff = TIFFOpen(file_name, "w");
  if (this->tiff == NULL)
    return IM_ERR_OPEN;

  this->tile_buf = 0;

  return IM_ERR_NONE;
}
