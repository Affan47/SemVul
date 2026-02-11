atom_tfra_new (AtomsContext * context, guint32 track_ID)
{
  AtomTFRA *tfra = g_new0 (AtomTFRA, 1);

  atom_tfra_init (tfra, track_ID);
  return tfra;

}
