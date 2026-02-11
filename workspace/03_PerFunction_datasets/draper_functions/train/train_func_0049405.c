getWord(const bool toUpper) {
	char *ret = NULL;
	ret = currentDict->getWord();
	if (toUpper) {
		ret = toUpperCase(ret, wordBuffer);
	}
	return ret;
}
