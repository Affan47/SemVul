mailfolder_add_child(struct mailfolder * parent,
    struct mailfolder * child)
{
  unsigned int indx;
  int r;

  r = carray_add(parent->fld_children, child, &indx);
  if (r < 0)
    return MAIL_ERROR_MEMORY;

  child->fld_sibling_index = indx;
  child->fld_parent = parent;

  return MAIL_NO_ERROR;
}
