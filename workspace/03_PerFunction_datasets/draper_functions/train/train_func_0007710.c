utf8_char_count(const uint8_t *bytes, unsigned int n, unsigned int *res)
{
	unsigned int result = 0;

	for (unsigned int i = 0; i < n; ++i) {
		++result;


		if (!(bytes[i] & 0x80)) {
			continue;
		}


		if ((bytes[i] & 0xe0) == 0xc0) {
			if (i + 1 >= n)
				return 1;
			if ((bytes[++i] & 0xc0) != 0x80)
				return 1;
			continue;
		}


		if ((bytes[i] & 0xf0) == 0xe0) {
			if (i + 2 >= n)
				return 1;
			if ((bytes[++i] & 0xc0) != 0x80)
				return 1;
			if ((bytes[++i] & 0xc0) != 0x80)
				return 1;
			continue;
		}


		return 1;
	}

	*res = result;
	return 0;
}
