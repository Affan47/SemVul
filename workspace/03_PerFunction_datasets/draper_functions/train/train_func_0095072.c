makeSymlink(const char* pathName, const char* target, Volume* volume) {
	io_func* io;
	HFSPlusCatalogFile* record;

	record = (HFSPlusCatalogFile*) getRecordFromPath3(pathName, volume, NULL, NULL, TRUE, FALSE, kHFSRootFolderID);

	if(!record) {
		newFile(pathName, volume);
		record = (HFSPlusCatalogFile*) getRecordFromPath(pathName, volume, NULL, NULL);
		if(!record) {
			return FALSE;
		}
		record->permissions.fileMode |= S_IFLNK;
		record->userInfo.fileType = kSymLinkFileType;
		record->userInfo.fileCreator = kSymLinkCreator;
		updateCatalog(volume, (HFSPlusCatalogRecord*) record);
	} else {
		if(record->recordType != kHFSPlusFileRecord || (((HFSPlusCatalogFile*)record)->permissions.fileMode & S_IFLNK) != S_IFLNK) {
			free(record);
			return FALSE;
		}
	}

	io = openRawFile(record->fileID, &record->dataFork, (HFSPlusCatalogRecord*) record, volume);
	WRITE(io, 0, strlen(target), (void*) target);
	CLOSE(io);
	free(record);

	return TRUE;
}
