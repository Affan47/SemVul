generate_random_string(char *str, int length)
{
	uint8_t val;
	int i;

	memset(str, '\0', length);

	for (i = 0; i < length-1; i++) {
		do {
			val = (uint8_t)(random() % 122);
			if (val < 48)
				val += 48;
		} while((val > 57 && val < 65) || (val > 90 && val < 97));

		str[i] = val;
	}
}
