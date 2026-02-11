match_glob(char *glob, char *str)
{


	while (*str != '\0') {


		if (*glob == '*') {
			if (match_glob(glob + 1, str)) {
				return 1;
			}
		} else if (*glob == '?' || *glob == *str) {
			++glob;
		} else {
			return 0;
		}

		++str;
	}


	while (*glob == '*') {
		++glob;
	}


	return *glob == '\0';
}
