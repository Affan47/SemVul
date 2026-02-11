atom_ctts_init (AtomCTTS * ctts)
{
  guint8 flags[3] = { 0, 0, 0 };

  atom_full_init (&ctts->header, FOURCC_ctts, 0, 0, 0, flags);
  atom_array_init (&ctts->entries, 128);
  ctts->do_pts = FALSE;
}
