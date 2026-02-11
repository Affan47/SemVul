Set(const char *s) {
	Clear();
	list = new char[strlen(s) + 1];
	strcpy(list, s);
	words = ArrayFromWordList(list, &len, onlyLineEnds);
	SortWordList(words, len);
	for (unsigned int k = 0; k < (sizeof(starts) / sizeof(starts[0])); k++)
		starts[k] = -1;
	for (int l = len - 1; l >= 0; l--) {
		unsigned char indexChar = words[l][0];
		starts[indexChar] = l;
	}
}
