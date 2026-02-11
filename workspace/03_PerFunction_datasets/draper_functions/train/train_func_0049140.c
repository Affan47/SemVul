PeekToken(char *indata, char **outdata)
{
	char *dummy;
	char *token;

	if (!outdata)
	{
		outdata = &dummy;
	}
	*outdata = DoPeekToken(indata, &token, NULL, NULL, NULL);

	return token;
}
