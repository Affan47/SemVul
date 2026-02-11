ArrayFromWordList(char *wordlist, int *len, bool onlyLineEnds = false) {
	int prev = '\n';
	int words = 0;


	bool wordSeparator[256];
	for (int i=0; i<256; i++) {
		wordSeparator[i] = false;
	}
	wordSeparator[static_cast<unsigned int>('\r')] = true;
	wordSeparator[static_cast<unsigned int>('\n')] = true;
	if (!onlyLineEnds) {
		wordSeparator[static_cast<unsigned int>(' ')] = true;
		wordSeparator[static_cast<unsigned int>('\t')] = true;
	}
	for (int j = 0; wordlist[j]; j++) {
		int curr = static_cast<unsigned char>(wordlist[j]);
		if (!wordSeparator[curr] && wordSeparator[prev])
			words++;
		prev = curr;
	}
	char **keywords = new char *[words + 1];
	int wordsStore = 0;
	const size_t slen = strlen(wordlist);
	if (words) {
		prev = '\0';
		for (size_t k = 0; k < slen; k++) {
			if (!wordSeparator[static_cast<unsigned char>(wordlist[k])]) {
				if (!prev) {
					keywords[wordsStore] = &wordlist[k];
					wordsStore++;
				}
			} else {
				wordlist[k] = '\0';
			}
			prev = wordlist[k];
		}
	}
	keywords[wordsStore] = &wordlist[slen];
	*len = wordsStore;
	return keywords;
}
