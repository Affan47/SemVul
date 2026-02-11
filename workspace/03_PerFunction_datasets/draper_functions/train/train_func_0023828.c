releaseResourceData(ResourceData* data) {
  ResourceData* curData;
  ResourceData* nextData;

  nextData = data;
  while(nextData != NULL) {
    curData = nextData;

    if(curData->name)
      free(curData->name);

    if(curData->data)
      free(curData->data);

    nextData = nextData->next;
    free(curData);
  }
}
