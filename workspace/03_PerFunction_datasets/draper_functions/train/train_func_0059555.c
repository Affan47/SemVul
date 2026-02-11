convbytes(char *input)
{
	char *units[] = { "Bytes", "KB", "MB", "GB", "TB", "PB" };
	char *endptr;
	static char output[50];
	float bytes;
	unsigned int i = 0;


	errno = 0;
	bytes = (float) strtod(input, &endptr);


	if (*endptr != '\0' || errno == ERANGE)
		return "Bad format";


	for (; i < (sizeof(units) / sizeof(char *)) - 1; i++) {
		if (bytes < 1024)
			break;
		bytes /= 1024;
	}

	snprintf(output, 50, "%.2f %s", bytes, units[i]);

	return output;
}
