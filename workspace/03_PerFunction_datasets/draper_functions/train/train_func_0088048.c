ipmi_parse_hex(const char *str)
{
	const char * p;
	unsigned char * out, *q;
	unsigned char b = 0;
	int shift = 4;

	if (strlen(str) == 0)
		return NULL;

	if (strlen(str) % 2 != 0) {
		lprintf(LOG_ERR, "Number of hex_kg characters is not even");
		return NULL;
	}

	if (strlen(str) > (IPMI_KG_BUFFER_SIZE-1)*2) {
		lprintf(LOG_ERR, "Kg key is too long");
		return NULL;
	}

	out = calloc(IPMI_KG_BUFFER_SIZE, sizeof(unsigned char));
	if (out == NULL) {
		lprintf(LOG_ERR, "malloc failure");
		return NULL;
	}

	for (p = str, q = out; *p; p++) {
		if (!isxdigit(*p)) {
			lprintf(LOG_ERR, "Kg_hex is not hexadecimal number");
			free(out);
			return NULL;
		}

		if (*p < 'A')
			b = *p - '0';
		else
			b = (*p | 0x20) - 'a' + 10;

		*q = *q + b << shift;
		if (shift)
			shift = 0;
		else {
			shift = 4;
			q++;
		}
    }

	return out;
}
