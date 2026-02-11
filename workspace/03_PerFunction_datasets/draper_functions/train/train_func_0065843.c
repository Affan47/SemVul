skipFreeAllItems(skipList list) {

  UINT32 i;
  skipItem x, y;

  x = list->header->next[0];

  while(x != list->tail) {
    y = x->next[0];
    skipFreeItem(list, x);
    x = y;
  }

  for(i = 0;
      i <= list->maxLevel;
      i++)
    list->header->next[i] = list->tail;

  return;
}
