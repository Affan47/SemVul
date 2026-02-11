GetTypeId (const string& Name)
{
	TypeId res = Types[Name];
	if (res == NoType)
		Types.erase (Name);
	return res;
}
