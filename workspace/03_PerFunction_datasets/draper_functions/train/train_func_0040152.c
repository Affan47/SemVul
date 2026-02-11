putString(const char *string, const char *desc)
{
	const char *pp = string ? (const char*)duppa(string, strlen(string)+1) : NULL;
	mStream->write(&pp, sizeof pp);
}
