datepart(const char *buf, int size, int min, int max, int *errp) {
	int result = 0;
	int i;

	for (i = 0; i < size; i++) {
		if (!isdigit((unsigned char)(buf[i])))
			*errp = 1;
		result = (result * 10) + buf[i] - '0';
	}
	if (result < min)
		*errp = 1;
	if (result > max)
		*errp = 1;
	return (result);
}
