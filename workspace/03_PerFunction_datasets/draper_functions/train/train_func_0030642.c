findlargestnodeleqlcpvalue(
                                          Mergertrienode *smallest,
                                          unsigned long lcpvalue,
                                          GtError *err)
{
  Mergertrienode *tmp;

  gt_error_check(err);
  for (tmp = smallest->parent; tmp != NULL; tmp = tmp->parent)
  {
    if (tmp->depth <= lcpvalue)
    {
      return tmp;
    }
  }
  gt_error_set(err,"path does not contain a node of depth <= %lu",
                lcpvalue);
  return NULL;
}
