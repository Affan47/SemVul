ReadImageData(void* data)
{
  imCounterTotal(this->counter, this->height, "Reading TGA...");

  int line_size = this->line_buffer_size;
  if (this->bpp == 16)
    line_size = this->width*2;

  for (int row = 0; row < this->height; row++)
  {
    if (this->image_type > 3)
    {
      if (iTGADecodeScanLine(handle, (imbyte*)this->line_buffer, this->width, this->bpp/8) == IM_ERR_ACCESS)
        return IM_ERR_ACCESS;
    }
    else
    {
      imBinFileRead(handle, this->line_buffer, line_size, 1);
      if (imBinFileError(handle))
        return IM_ERR_ACCESS;
    }

    if (this->bpp > 8)
      FixRGB();

    imFileLineBufferRead(this, data, row, 0);

    if (!imCounterInc(this->counter))
      return IM_ERR_COUNTER;
  }

  return IM_ERR_NONE;
}
