format_by_fourcc(int fourcc)
{
	unsigned int i;

	for (i = 0; i < FORMATS; i++) {
		if (-1 == formats[i].fourcc)
			continue;
		if (formats[i].fourcc == fourcc)
			return formats+i;
	}
	return NULL;
}
