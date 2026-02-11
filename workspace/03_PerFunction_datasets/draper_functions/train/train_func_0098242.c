AppendVarBind(VarBindList *list)
{
  AsnListNode *newNode;
  VarBind *entry;

  newNode  = alloc_t(AsnListNode);
  newNode->data = alloc_t(VarBind);
  newNode->next = NULL;

  if(list->last == NULL)
    {
      newNode->prev = NULL;
      list->first = newNode;
      list->last = newNode;
    }
  else
    {
      newNode->prev = list->last;
      list->last->next = newNode;
      list->last = newNode;
    }

  list->curr = newNode;
  list->count++;

  return newNode->data;
}
