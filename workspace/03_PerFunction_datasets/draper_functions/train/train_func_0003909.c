sanityCheck()
{
	if (!ptr.isDestroyed() && messageNum < ptr->getFolderIndexSize() &&
	    uid == ptr->getFolderIndexInfo(messageNum).uid)
		return true;
	checkSearch();
	return false;
}
