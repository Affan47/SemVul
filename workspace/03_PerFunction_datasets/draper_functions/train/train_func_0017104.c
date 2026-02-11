print() const
{
	Tconstantmap::const_iterator it;
	for (it = cmap.begin(); it != cmap.end(); ++it)
		printf("$%d:  %8.4g\n", (*it).first, (*it).second);
}
