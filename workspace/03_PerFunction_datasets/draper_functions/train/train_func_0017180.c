lto_input_data_block (struct lto_input_block *ib, void *addr, size_t length)
{
  size_t i;
  unsigned char *const buffer = (unsigned char *const) addr;

  for (i = 0; i < length; i++)
    buffer[i] = streamer_read_uchar (ib);
}
