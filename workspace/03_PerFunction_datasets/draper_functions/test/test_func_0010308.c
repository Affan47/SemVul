CreateEntry(const string& entry)
{
	TNameSpace *ns=SearchNameSpace(entry);
	return ((ns)?ns->Create(entry): TEntry(GlobalNameSpace,0));
}
