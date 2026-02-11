str_cmp(const char* a, int a_len, const char* b, int b_len)
{
	int i = 0;

	if (a_len == -1) {
		a_len = 0;
		while (a[a_len]) a_len++;
	}
	if (b_len == -1) {
		b_len = 0;
		while (b[b_len]) b_len++;
	}
	while (1) {
		if (i >= a_len) {
			if (i >= b_len)
				return 0;
			return -1;
		}
		if (i >= b_len) {
			if (i >= a_len)
				return 0;
			return 1;
		}
		if (a[i] != b[i])
			return a[i] - b[i];
		i++;
	}
}
