GMT_chop (char *string)
{

	GMT_LONG i, n;
	if (!string) return;
	if ((n = (GMT_LONG)strlen (string)) == 0) return;
	for (i = n - 1; i >= 0 && (string[i] == '\n' || string[i] == '\r'); i--);
	i++;
	if (i >= 0) string[i] = '\0';
}
