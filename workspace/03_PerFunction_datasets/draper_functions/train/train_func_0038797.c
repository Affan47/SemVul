CheckAPDLFoldPoint(char const *token, int &level) {
	if (!strcmp(token, "*if") ||
		!strcmp(token, "*do") ||
		!strcmp(token, "*dowhile") ) {
		level |= SC_FOLDLEVELHEADERFLAG;
		return 1;
	}
	if (!strcmp(token, "*endif") ||
		!strcmp(token, "*enddo") ) {
		return -1;
	}
	return 0;
}
