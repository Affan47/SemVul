options(int argc, char** argv, const char *legal)
{
	static char *posn = "";
	char *legal_index = NULL;
	int letter = 0;

	if (!*posn) {
		if ((OptIndex >= argc)
		    || (*(posn = argv[OptIndex]) != sw_char)
		    || !*++posn)
				return -1;

		if (*posn == sw_char) {
			OptIndex++;
			return -1;
		}
	}

	letter = *posn++;

	if (!(legal_index = strchr(legal, letter))) {
		if (!*posn)
			OptIndex++;
		return unknown_opt;
	}

	if (*++legal_index != ':') {
		OptArg = NULL;
		if (!*posn)
			OptIndex++;
	}
	else {
		if (*posn)
			OptArg = posn;
		else
			if (argc <= ++OptIndex) {
				posn = "";
				return unknown_opt;
			}
			else
				OptArg = argv[OptIndex];
		posn = "";
		OptIndex++;
	}
	return letter;
}
