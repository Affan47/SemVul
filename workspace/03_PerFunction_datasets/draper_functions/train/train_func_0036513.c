dictFreeItem(dictCtx dict, dictItemPtr item) {

  if(dict->freeValue)
    dict->freeValue(item->value, dict->freeRock);
  free(item->id);
  free(item);

  return;
}
