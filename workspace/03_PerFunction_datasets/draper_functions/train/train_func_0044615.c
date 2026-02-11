iFixAdobeCMYK(unsigned char* line_buffer, int width)
{
  width *= 4;
  for (int i = 0; i < width; i++)
  {
    *line_buffer = 255 - *line_buffer;
    line_buffer++;
  }
}
