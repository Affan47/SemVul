str2ic(const char *s)
{
	int i = 0;
	int j, k;

	if (*s != '-') {

		while (1) {
			j = (*s++) - '0';
			k = i * 10;
			if ((unsigned)j > 9)
				break;
			i = k + j;
		}
	} else {

		s++;
		while (1) {
			j = (*s++) - '0';
			k = i * 10;
			if ((unsigned)j > 9)
				break;
			i = k - j;
		}
	}

	return i;
}
