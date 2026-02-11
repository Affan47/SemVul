readndigits(char **const buf, const size_t count)
{
	int result = 0;
	int i;

	for (i = 0; i < count; i++, (*buf)++) {
		const char digit = **buf;
		if (digit == 0 || !isdigit(digit)) {
			break;
		}
		result *= 10;
		result += digit - '0';
	}

	return result;
}
