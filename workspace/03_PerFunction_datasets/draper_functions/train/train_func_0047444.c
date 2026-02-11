ast_print_group(char *buf, int buflen, ast_group_t group)
{
	unsigned int i;
	int first = 1;
	char num[3];

	buf[0] = '\0';

	if (!group)
		return buf;

	for (i = 0; i <= 63; i++) {
		if (group & ((ast_group_t) 1 << i)) {
			if (!first) {
				strncat(buf, ", ", buflen - strlen(buf) - 1);
			} else {
				first = 0;
			}
			snprintf(num, sizeof(num), "%u", i);
			strncat(buf, num, buflen - strlen(buf) - 1);
		}
	}
	return buf;
}
