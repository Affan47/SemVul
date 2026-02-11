interpolate(char *result, unsigned long reslen,
		const char *orig,
		const struct interp *interps, int ninterps)
{
	const char *src = orig;
	char *dest = result;
	unsigned long newlen = 0;
	const char *name, *value;
	unsigned long namelen, valuelen;
	int i;
	char c;

	while ((c = *src)) {
		if (c == '%') {

			for (i = 0; i < ninterps; i++) {
				name = interps[i].name;
				namelen = strlen(name);
				if (strncmp(src, name, namelen) == 0)
					break;
			}


			if (i < ninterps) {
				value = interps[i].value;
				if (!value) {
					src += namelen;
					continue;
				}

				valuelen = strlen(value);
				if (newlen + valuelen < reslen) {

					memcpy(dest, value, valuelen);
					dest += valuelen;
				}
				newlen += valuelen;
				src += namelen;
				continue;
			}
		}

		if (newlen + 1 < reslen)
			*dest++ = *src;
		src++;
		newlen++;
	}


	if (reslen > 0)
		*dest = '\0';
	return newlen;
}
