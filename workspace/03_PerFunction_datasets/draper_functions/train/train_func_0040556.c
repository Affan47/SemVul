atom_mvex_copy_data (AtomMVEX * mvex, guint8 ** buffer, guint64 * size,
    guint64 * offset)
{
  guint64 original_offset = *offset;
  GList *walker;

  if (!atom_copy_data (&mvex->header, buffer, size, offset)) {
    return 0;
  }

  if (!atom_mehd_copy_data (&mvex->mehd, buffer, size, offset)) {
    return 0;
  }

  walker = g_list_first (mvex->trexs);
  while (walker != NULL) {
    if (!atom_trex_copy_data ((AtomTREX *) walker->data, buffer, size, offset)) {
      return 0;
    }
    walker = g_list_next (walker);
  }

  atom_write_size (buffer, size, offset, original_offset);
  return *offset - original_offset;
}
