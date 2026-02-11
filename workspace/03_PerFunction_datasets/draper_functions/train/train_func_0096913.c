fs_chain_find(format_specific_data* chain, long type)
{
  format_specific_data* cur = chain;
  while (cur) {
    if (cur->type == type) {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
}
