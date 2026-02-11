trim_string(char *str)
{
	char *ptr;
	int len;

	if (str == NULL)
		return NULL;


	ptr = strchr(str, ';');
	if (ptr)
		*ptr = 0;
	ptr = strchr(str, '#');
	if (ptr)
		*ptr = 0;

	ptr = str;
	len = strlen(str);
	if (len > 0) {
		ptr += len-1;
	}

	while ((ptr > str) && isspace(*ptr)) {
		ptr--;
	}

	if (*ptr) {
		ptr++;
		*ptr = 0;
	}

	ptr = str;
	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	return ptr;
}
