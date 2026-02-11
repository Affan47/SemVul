skipPastNestedToken(tokenInfo *const token, tokenType openType,
		tokenType closeType)
{
	int nesting = 0;

	do
	{
		if (isType(token, openType))
			++nesting;
		else if (isType(token, closeType))
			--nesting;

		readToken(token);
	}
	while (nesting > 0);
}
