Regex_namedCaptures(Regex *self)
{
	NamedCapture *namedCaptures = 0;
	NamedCapture *capture = 0;
	int nameCount = 0;
	int entrySize = 0;
	unsigned char *entry = 0;
	int i = 0;

	Regex_put_in_(self, PCRE_INFO_NAMECOUNT, &nameCount);
	if (nameCount <= 0)
		return 0;

	capture = namedCaptures = calloc(nameCount + 1, sizeof(NamedCapture));

	Regex_put_in_(self, PCRE_INFO_NAMEENTRYSIZE, &entrySize);
	Regex_put_in_(self, PCRE_INFO_NAMETABLE, &entry);

	for (i = 0; i < nameCount; i++) {
		capture->name = (const char*)(entry + 2);
		capture->index = (entry[0] << 8) | entry[1];
		capture++;

		entry += entrySize;
	}

	return namedCaptures;
}
