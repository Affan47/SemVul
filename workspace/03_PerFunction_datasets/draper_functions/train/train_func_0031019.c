writeNSiz(NSizResource* nSiz) {
  NSizResource* curNSiz;
  ResourceKey* key;
  ResourceData* curData;
  char buffer[1024];

  curNSiz = nSiz;

  key = (ResourceKey*) malloc(sizeof(ResourceKey));
  key->key = (unsigned char*) malloc(sizeof("nsiz") + 1);
  strcpy((char*) key->key, "nsiz");
  key->next = NULL;
  key->flipData = NULL;
  key->data = NULL;

  while(curNSiz != NULL) {
    writeNSizResource(curNSiz, buffer);
    if(key->data == NULL) {
      key->data = (ResourceData*) malloc(sizeof(ResourceData));
      curData = key->data;
    } else {
      curData->next = (ResourceData*) malloc(sizeof(ResourceData));
      curData = curData->next;
    }

    curData->attributes = 0;
    curData->id = curNSiz->partitionNumber;
    curData->name = (char*) malloc(sizeof(char));
    curData->name[0] = '\0';
    curData->next = NULL;
    curData->dataLength = sizeof(char) * strlen(buffer);
    curData->data = (unsigned char*) malloc(curData->dataLength);
    memcpy(curData->data, buffer, curData->dataLength);

    curNSiz = curNSiz->next;
  }

  return key;
}
