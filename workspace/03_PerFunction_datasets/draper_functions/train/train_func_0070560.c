CompareNCaseInsensitive(const char *a, const char *b, size_t len) {
	while (*a && *b && len) {
		if (*a != *b) {
			char upperA = MakeUpperCase(*a);
			char upperB = MakeUpperCase(*b);
			if (upperA != upperB)
				return upperA - upperB;
		}
		a++;
		b++;
		len--;
	}
	if (len == 0)
		return 0;
	else

		return *a - *b;
}
