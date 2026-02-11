mark_all_entries(SplitStruct *node, int n_entries, int n_group)
{
  SplitStruct *cur = node;
  SplitStruct *end = node + n_entries;
  for (; cur<end; ++cur)
  {
    if (cur->n_node)
    {
      continue;
    }
    cur->n_node = n_group;
  }
}
