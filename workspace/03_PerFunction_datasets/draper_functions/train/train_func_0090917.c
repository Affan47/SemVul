mailfolder_detach_parent(struct mailfolder * folder)
{
  unsigned int i;
  int r;

  if (folder->fld_parent == NULL)
    return MAIL_ERROR_INVAL;

  r = carray_delete_slow(folder->fld_parent->fld_children,
      folder->fld_sibling_index);
  if (r < 0)
    return MAIL_ERROR_INVAL;

  for(i = 0 ; i < carray_count(folder->fld_parent->fld_children) ; i ++) {
    struct mailfolder * child;

    child = carray_get(folder->fld_parent->fld_children, i);
    child->fld_sibling_index = i;
  }

  folder->fld_parent = NULL;
  folder->fld_sibling_index = 0;

  return MAIL_NO_ERROR;
}
