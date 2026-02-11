move(GtRBTreeIter *trav, int dir, GT_UNUSED bool strict)
{
  if (trav->it->link[dir] != NULL) {

    trav->path[trav->top++] = trav->it;
    trav->it = trav->it->link[dir];

    while (trav->it->link[(int) !dir] != NULL) {
      trav->path[trav->top++] = trav->it;
      trav->it = trav->it->link[(int) !dir];
    }
  } else {

    GtRBTreeNode *last;

    do {
      if (trav->top == 0) {
        trav->it = NULL;
        break;
      }

      last = trav->it;
      trav->it = trav->path[--trav->top];
    } while (last == trav->it->link[dir]);
  }

  return trav->it == NULL ? NULL : trav->it->key;
}
