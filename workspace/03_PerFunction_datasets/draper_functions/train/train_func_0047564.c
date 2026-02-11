PortList_get_nth(PortList* pl, int n)
{
  PortListNode* tmp;
  assert(pl != NULL);
  if (pl == NULL) {
    return NULL;
  }
  assert(n >= 0);
  assert(n < PortList_get_size(pl));
  tmp = pl->head;
  while (tmp) {
    if (n <= 0) {
      return tmp;
    }
    n -= 1;
    tmp = PortListNode_get_nextNode(tmp);
  }
  return NULL;
}
