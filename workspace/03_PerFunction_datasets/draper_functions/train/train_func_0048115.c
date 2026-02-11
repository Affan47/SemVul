SkipNTokens(char *indata, unsigned int n)
{
	for ( ; n > 0 && indata != NULL && *indata != 0; n--)
	{
		PeekToken(indata, &indata);
	}

	return indata;
}
