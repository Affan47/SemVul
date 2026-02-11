cleanup(char *line)
{
	int len = strlen(line);

	if (len && line[len-1] == '\n') {
		if (len == 1)
			return 0;
		do {
			unsigned char c = line[len-2];
			if (!isspace(c))
				break;
			line[len-2] = '\n';
			len--;
			line[len] = 0;
		} while (len > 1);
		return 0;
	}
	return 1;
}
