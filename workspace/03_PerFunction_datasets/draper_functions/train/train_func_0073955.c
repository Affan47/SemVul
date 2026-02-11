lto_input_location (struct lto_input_block *ib, struct data_in *data_in)
{
  if (streamer_hooks.input_location)
    return streamer_hooks.input_location (ib, data_in);
  else
    {
      struct bitpack_d bp;

      bp = streamer_read_bitpack (ib);
      return lto_input_location_bitpack (data_in, &bp);
    }
}
