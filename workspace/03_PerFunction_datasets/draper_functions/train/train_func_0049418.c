removeFile(const char* fileName, Volume* volume) {
  HFSPlusCatalogRecord* record;
  HFSPlusCatalogKey key;
  io_func* io;
  HFSPlusCatalogFolder* parentFolder;

  record = getRecordFromPath3(fileName, volume, NULL, &key, TRUE, FALSE, kHFSRootFolderID);
  if(record != NULL) {
    parentFolder = (HFSPlusCatalogFolder*) getRecordByCNID(key.parentID, volume);
    if(parentFolder != NULL) {
	if(parentFolder->recordType != kHFSPlusFolderRecord) {
		ASSERT(FALSE, "parent not folder");
		free(parentFolder);
		return FALSE;
	}
    } else {
	ASSERT(FALSE, "can't find parent");
	return FALSE;
    }

    if(record->recordType == kHFSPlusFileRecord) {
      io = openRawFile(((HFSPlusCatalogFile*)record)->fileID, &((HFSPlusCatalogFile*)record)->dataFork, record, volume);
      allocate((RawFile*)io->data, 0);
      CLOSE(io);

      removeFromBTree(volume->catalogTree, (BTKey*)(&key));

      key.nodeName.length = 0;
      key.parentID = ((HFSPlusCatalogFile*)record)->fileID;
      key.keyLength = sizeof(key.parentID) + sizeof(key.nodeName.length);
      removeFromBTree(volume->catalogTree, (BTKey*)(&key));

      volume->volumeHeader->fileCount--;
    } else {
      if(((HFSPlusCatalogFolder*)record)->valence > 0) {
		free(record);
		free(parentFolder);
		ASSERT(FALSE, "folder not empty");
        return FALSE;
      } else {
        removeFromBTree(volume->catalogTree, (BTKey*)(&key));

        key.nodeName.length = 0;
        key.parentID = ((HFSPlusCatalogFolder*)record)->folderID;
        key.keyLength = sizeof(key.parentID) + sizeof(key.nodeName.length);
        removeFromBTree(volume->catalogTree, (BTKey*)(&key));
      }

	  parentFolder->folderCount--;
      volume->volumeHeader->folderCount--;
    }
    parentFolder->valence--;
    updateCatalog(volume, (HFSPlusCatalogRecord*) parentFolder);
    updateVolume(volume);

	free(record);
	free(parentFolder);

    return TRUE;
  } else {
	free(parentFolder);
	ASSERT(FALSE, "cannot find record");
    return FALSE;
  }
}
