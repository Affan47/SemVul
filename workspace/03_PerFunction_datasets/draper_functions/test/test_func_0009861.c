hex_to_string(char *hexstring)
{
	char *ret = NULL;
	char buf[3], *endptr;
	size_t len;
	int i;

	if (!hexstring)
		goto out;

	len = strlen(hexstring) / 2;
	ret = malloc(len + 1);
	if (!ret)
		goto out;

	for (i = 0; i < len; i++) {
		sprintf(buf, "%.2s", hexstring);
		hexstring += 2;
		ret[i] = (unsigned char) strtoul(buf, &endptr, 16);
	}
	ret[len] = '\0';

out:
	return ret;
}
