writeResources(AbstractFile* file, ResourceKey* resources) {
  ResourceKey* curResource;
  ResourceData* curData;

  abstractFilePrint(file, plistHeader);
  abstractFilePrint(file, "\t<key>resource-fork</key>\n\t<dict>\n");

  curResource = resources;
  while(curResource != NULL) {
    abstractFilePrint(file, "\t\t<key>%s</key>\n\t\t<array>\n", curResource->key);
    curData = curResource->data;
    while(curData != NULL) {
	    writeResourceData(file, curData, curResource, curResource->flipData, 3);
	    curData = curData->next;
    }
    abstractFilePrint(file, "\t\t</array>\n", curResource->key);
    curResource = curResource->next;
  }

  abstractFilePrint(file, "\t</dict>\n");
  abstractFilePrint(file, plistFooter);

}
