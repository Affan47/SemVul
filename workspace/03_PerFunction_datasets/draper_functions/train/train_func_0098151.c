streamer_read_uhwi (struct lto_input_block *ib)
{
  unsigned HOST_WIDE_INT result = 0;
  int shift = 0;
  unsigned HOST_WIDE_INT byte;

  while (true)
    {
      byte = streamer_read_uchar (ib);
      result |= (byte & 0x7f) << shift;
      shift += 7;
      if ((byte & 0x80) == 0)
	return result;
    }
}
