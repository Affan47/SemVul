ecdsa_sig_to_der(const uint8_t *sig, uint8_t *der)
{
	int i;
	uint8_t *p = der, *len, *len1, *len2;
	*p = 0x30; p++;
	*p = 0x00; len = p; p++;

	*p = 0x02; p++;
	*p = 0x00; len1 = p; p++;


	i = 0;
	while (sig[i] == 0 && i < 32) { i++; }
	if (sig[i] >= 0x80) {
		*p = 0x00; p++; *len1 = *len1 + 1;
	}
	while (i < 32) {
		*p = sig[i]; p++; *len1 = *len1 + 1; i++;
	}

	*p = 0x02; p++;
	*p = 0x00; len2 = p; p++;


	i = 32;
	while (sig[i] == 0 && i < 64) { i++; }
	if (sig[i] >= 0x80) {
		*p = 0x00; p++; *len2 = *len2 + 1;
	}
	while (i < 64) {
		*p = sig[i]; p++; *len2 = *len2 + 1; i++;
	}

	*len = *len1 + *len2 + 4;
	return *len + 2;
}
