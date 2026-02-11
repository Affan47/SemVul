set_downenc(char *encoding)
{
	if (!strcasecmp(encoding, "base32"))
		downenc = 'T';
	else if (!strcasecmp(encoding, "base64"))
		downenc = 'S';
	else if (!strcasecmp(encoding, "base64u"))
		downenc = 'U';
	else if (!strcasecmp(encoding, "base128"))
		downenc = 'V';
	else if (!strcasecmp(encoding, "raw"))
		downenc = 'R';
}
