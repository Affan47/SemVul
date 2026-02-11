sc_free (void *pointer)
{
  if (sc_zero_allocation != &sc_zero_allocation)
    sc_fatal ("sc_free: write to zero-byte allocation address detected\n");

  if (pointer && pointer != sc_zero_allocation)
    free (pointer);
}
