Append(char *s, int type) {
  FXXPMIcon * icon = NULL;
  if ((type >= 0) && pixhash) {
    map<int, FXXPMIcon *>::iterator it = pixhash->find(type);
    if (it != pixhash->end())
      icon = (*it).second;
  }
  list->appendItem(s, icon);
  size_t len = strlen(s);
  if (maxItemCharacters < len)
          maxItemCharacters = len;
  if (list->getNumItems() <= desiredVisibleRows)
    list->setNumVisible(list->getNumItems());
  list->sortItems();
}
