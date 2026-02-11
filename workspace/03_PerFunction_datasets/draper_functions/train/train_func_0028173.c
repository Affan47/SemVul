is_word(const char* cmdline, const char* keyword, char** cptr) {
	int len = strlen(keyword);
	if (strncmp(cmdline, keyword, len))
		return 0;
	*cptr = (char*)(cmdline + len);
	return 1;
}
