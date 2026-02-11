atom_meta_free (AtomMETA * meta)
{
  atom_full_clear (&meta->header);
  atom_hdlr_clear (&meta->hdlr);
  if (meta->ilst)
    atom_ilst_free (meta->ilst);
  meta->ilst = NULL;
  g_free (meta);
}
