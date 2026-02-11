iax_provflags2str(char *buf, int buflen, unsigned int flags)
{
	int x;

	if (!buf || buflen < 1)
		return NULL;

	buf[0] = '\0';

	for (x = 0; x < ARRAY_LEN(iax_flags); x++) {
		if (flags & iax_flags[x].value){
			strncat(buf, iax_flags[x].name, buflen - strlen(buf) - 1);
			strncat(buf, ",", buflen - strlen(buf) - 1);
		}
	}

	if (!ast_strlen_zero(buf))
		buf[strlen(buf) - 1] = '\0';
	else
		strncpy(buf, "none", buflen - 1);

	return buf;
}
