search_ap_def_use(Def_use_table **ret_def_use, Def_use_table *head, Ap_copy_out *ap_co)
{
  Def_use_table *curr;
  int ret = FALSE;

  for (curr = head; curr; curr = curr->next) {
    if (curr->table == ap_co->table &&
        curr->entry == ap_co->cm_entry) {
      ret = TRUE;
      break;
    }
  }
  (*ret_def_use) = (ret ? curr : NULL);
  return (ret);
}
