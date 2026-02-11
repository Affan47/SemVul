DirectoryMgrCurrentEntry(dm)
DirectoryMgr *dm;
{
	int index;

	index = DirectoryMgrCurrentIndex(dm);
	if (index < 0 || index >= DirectoryMgrFilteredCount(dm)) return(NULL);
	return(DirectoryMgrSortedPtrs(dm)[index]);
}
