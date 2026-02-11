atom_dref_clear (AtomDREF * dref)
{
  GList *walker;

  atom_full_clear (&dref->header);
  walker = dref->entries;
  while (walker) {
    GList *aux = walker;
    Atom *atom = (Atom *) aux->data;

    walker = g_list_next (walker);
    dref->entries = g_list_remove_link (dref->entries, aux);
    switch (atom->type) {
      case FOURCC_alis:
        atom_full_free ((AtomFull *) atom);
        break;
      case FOURCC_url_:
        atom_url_free ((AtomURL *) atom);
        break;
      default:

        break;
    }
    g_list_free (aux);
  }
}
