objprop_show_in_listview(const struct objprop *op)
{
  if (!op) {
    return FALSE;
  }
  return op->flags & OPF_IN_LISTVIEW;
}
