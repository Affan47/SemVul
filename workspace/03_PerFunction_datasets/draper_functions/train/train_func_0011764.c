raid_setup(char *str)
{
	int len, pos;

	len = strlen(str) + 1;
	pos = 0;

	while (pos < len) {
		char *comma = strchr(str+pos, ',');
		int wlen;
		if (comma)
			wlen = (comma-str)-pos;
		else	wlen = (len-1)-pos;

		if (!strncmp(str, "noautodetect", wlen))
			raid_noautodetect = 1;
		if (!strncmp(str, "autodetect", wlen))
			raid_noautodetect = 0;
		if (strncmp(str, "partitionable", wlen)==0)
			raid_autopart = 1;
		if (strncmp(str, "part", wlen)==0)
			raid_autopart = 1;
		pos += wlen+1;
	}
	return 1;
}
