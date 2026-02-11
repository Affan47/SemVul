IsAHexCharacter(const int iChar, bool bCaseSensitive) {


	if (!bCaseSensitive) {
		if (strchr("ABCDEFabcdef", iChar) != NULL) {
			return(true);
		}
	}

	else {
		if (strchr("ABCDEF", iChar) != NULL) {
			return(true);
		}
	}
	return(false);
}
