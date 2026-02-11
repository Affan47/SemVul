htab_traverse (htab, callback, info)
     htab_t htab;
     htab_trav callback;
     PTR info;
{
  if ((htab->n_elements - htab->n_deleted) * 8 < htab->size)
    htab_expand (htab);

  htab_traverse_noresize (htab, callback, info);
}
