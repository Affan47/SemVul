FixBinary()
{
  unsigned char* buf = (unsigned char*)this->line_buffer;
  for (int b = 0; b < this->line_buffer_size; b++)
  {
    *buf = ~(*buf);
    buf++;
  }
}
