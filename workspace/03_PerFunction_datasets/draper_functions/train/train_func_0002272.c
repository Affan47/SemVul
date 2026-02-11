streamer_read_hwi (struct lto_input_block *ib)
{
  HOST_WIDE_INT result = 0;
  int shift = 0;
  unsigned HOST_WIDE_INT byte;

  while (true)
    {
      byte = streamer_read_uchar (ib);
      result |= (byte & 0x7f) << shift;
      shift += 7;
      if ((byte & 0x80) == 0)
	{
	  if ((shift < HOST_BITS_PER_WIDE_INT) && (byte & 0x40))
	    result |= - ((HOST_WIDE_INT)1 << shift);

	  return result;
	}
    }
}
