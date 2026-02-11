getNumDataMembers(const char *key) const
{
	if(exists(key))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
