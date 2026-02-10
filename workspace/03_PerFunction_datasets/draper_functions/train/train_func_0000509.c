FreeRedoListHead(void) {
  if (RedoList) {
    UndoScoreElement *elem = RedoList->data;
    RedoList = g_list_remove(RedoList, elem);
    g_free(elem);
  }
}
