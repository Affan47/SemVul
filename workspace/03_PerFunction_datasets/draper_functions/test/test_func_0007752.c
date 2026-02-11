apdu_prepare_exit (void)
{
  static int sentinel;
  int slot;

  if (!sentinel)
    {
      sentinel = 1;
      for (slot = 0; slot < MAX_READER; slot++)
        if (reader_table[slot].used)
          {
            apdu_disconnect (slot);
            if (reader_table[slot].close_reader)
              reader_table[slot].close_reader (slot);
            reader_table[slot].used = 0;
          }
      sentinel = 0;
    }
}
