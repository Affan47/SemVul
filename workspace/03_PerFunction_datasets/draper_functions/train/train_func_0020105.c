ap_str(s)
	char *s;
{
	int len;

	len = strlen(s);
	if (mp + len >= message + PROMPT_SIZE)
		len = message + PROMPT_SIZE - mp - 1;
	strncpy(mp, s, len);
	mp += len;
	*mp = '\0';
}
