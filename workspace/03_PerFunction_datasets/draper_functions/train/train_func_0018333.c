reserved_kword(const char *ksym) {
	if (ksym == NULL)
		return 0;
	if (strcmp(ksym,"NUMBER_OF_FIELDS") == 0)
		return 1;
	if (strcmp(ksym,"BEGIN_DATA_FORMAT") == 0)
		return 1;
	if (strcmp(ksym,"END_DATA_FORMAT") == 0)
		return 1;
	if (strcmp(ksym,"NUMBER_OF_SETS") == 0)
		return 1;
	if (strcmp(ksym,"BEGIN_DATA") == 0)
		return 1;
	if (strcmp(ksym,"END_DATA") == 0)
		return 1;
	if (strcmp(ksym,"KEYWORD") == 0)
		return 1;
	return 0;
}
