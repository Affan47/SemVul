enum_list(int first, int last)
{
	char buf[50];
	for(int i = first; i <= last; i++)
	{
		snprintf(buf, sizeof(buf), "%d", i);
		item(buf, i);
	}
}
