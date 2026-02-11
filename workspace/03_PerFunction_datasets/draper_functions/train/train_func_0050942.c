ccf_set_specially_allocated(
    cct_8_8_dither_table table,
    unsigned char entry,
    unsigned int pixel)
{
  int c;
  for(c = 0; c < 4; c++)
  {
    table->pixel_values[c][entry] = pixel;
  }
}
