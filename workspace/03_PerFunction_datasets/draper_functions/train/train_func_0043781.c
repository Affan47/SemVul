AppendListNode(VarBindList *list, AsnListNode *node)
{
  node->next = NULL;
  if(list->last == NULL)
    {
      node->prev = NULL;
      list->first = node;
      list->last = node;
    }
  else
    {
      node->prev = list->last;
      list->last->next = node;
      list->last = node;
    }

  list->curr = node;
  list->count++;

  return;
}
