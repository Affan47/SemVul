atom_stsc_init (AtomSTSC * stsc)
{
  guint8 flags[3] = { 0, 0, 0 };

  atom_full_init (&stsc->header, FOURCC_stsc, 0, 0, 0, flags);
  atom_array_init (&stsc->entries, 128);
}
