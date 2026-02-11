symmap_check(FILE *in)
{
	char buf[128];
	int i;
	int spc_count = 0;

	rewind(in);
	if (!fgets(buf, sizeof(buf), in))
		return 0;

	for (i = 0; buf[i]; i++) {
		if (buf[i] == '\r' || buf[i] == '\n')
			break;

		if (buf[i] < 32 || buf[i] > 126)
			return 0;

		if (isspace(buf[i]))
			spc_count++;
	}

	return spc_count >= 2;
}
