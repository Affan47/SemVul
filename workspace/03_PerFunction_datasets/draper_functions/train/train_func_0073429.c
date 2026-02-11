check_name(char *name)
{
	int i, len = strlen(name);


	if (!len || !isalnum(name[0]) || !isalnum(name[len-1]))
		return 0;

	for (i = 0; i < len; i++) {
		if (!isalnum(name[i]) && name[i] != '-' && name[i] != '.')
			return 0;
		if (name[i] == '-' && (name[i - 1] == '.' || name[i + 1] == '.'))
			return 0;
		if (name[i] == '.' && name[i - 1] == '.')
			return 0;
	}

	return 1;
}
