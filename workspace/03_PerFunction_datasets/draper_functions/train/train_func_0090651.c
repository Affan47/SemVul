lf_convert_8_32(
  cct_8_true_conversion_table table,
  unsigned char *input,
  unsigned int *output,
  int pixel_count)
{
  int x;
  for(x = pixel_count; x; x--)
  {
    output[0] = table->pixel_values[input[0]];
    output++;
    input++;
  }
}
