set_int(const char *key, const char *value)
{
	char *endp;
	long longval;
	int error;

	errno = 0;
	longval = strtol(value, &endp, 10);
	error = errno;
	while (i_isspace(*endp))
		endp++;
	if (error != 0 || *endp != '\0' || longval < INT_MIN || longval > INT_MAX)
		printformat(NULL, NULL, MSGLEVEL_CLIENTERROR, TXT_INVALID_NUMBER);
	else
		settings_set_int(key, (int)longval);
}
