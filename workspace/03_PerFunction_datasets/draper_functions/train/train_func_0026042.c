verify_ace_type(char *typestr, uint8_t *typeval)
{
	int i, len;
	char *invaltype;

	if (strstr(typestr, "0x")) {
		*typeval = strtol(typestr, &invaltype, 16);
		if (!strlen(invaltype)) {
			if (*typeval != ACCESS_ALLOWED &&
				*typeval != ACCESS_DENIED &&
				*typeval != ACCESS_ALLOWED_OBJECT &&
				*typeval != ACCESS_DENIED_OBJECT) {
					printf("%s: Invalid type: %s\n",
						__func__, typestr);
					return 1;
			}
			return 0;
		}
	}

	len = strlen(typestr);
	for (i = 0; i < len; ++i)
		*(typestr + i) = toupper(*(typestr + i));
	if (!strcmp(typestr, "ALLOWED"))
		*typeval = 0x0;
	else if (!strcmp(typestr, "DENIED"))
		*typeval = 0x1;
	else if (!strcmp(typestr, "ALLOWED_OBJECT"))
		*typeval = 0x5;
	else if (!strcmp(typestr, "DENIED_OBJECT"))
		*typeval = 0x6;
	else {
		printf("%s: Invalid type: %s\n", __func__, typestr);
		return 1;
	}

	return 0;
}
