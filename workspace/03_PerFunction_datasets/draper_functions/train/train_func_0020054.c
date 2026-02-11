atom_tfra_free (AtomTFRA * tfra)
{
  atom_full_clear (&tfra->header);
  atom_array_clear (&tfra->entries);
  g_free (tfra);
}
