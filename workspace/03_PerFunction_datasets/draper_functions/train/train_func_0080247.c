remove_obsoletes (msgdomain_list_ty *mdlp)
{
  size_t k;

  for (k = 0; k < mdlp->nitems; k++)
    message_list_remove_if_not (mdlp->item[k]->messages, is_message_selected);

  return mdlp;
}
