RedoHead(void) {
  if (RedoList) {
    UndoScoreElement *elem = RedoList->data;
    return elem;
  }

  return NULL;
}
