getFolderFromString(string name)
{
	if (disconnected())
		return NULL;
	return ptr->folderFromString(name);
}
