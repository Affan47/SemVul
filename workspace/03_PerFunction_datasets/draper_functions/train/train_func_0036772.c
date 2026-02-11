prevToken (const statementInfo *const st, unsigned int n)
{
	unsigned int tokenIndex;
	unsigned int num = (unsigned int) NumTokens;
	Assert(n < num);
	tokenIndex = (st->tokenIndex + num - n) % num;

	return st->token[tokenIndex];
}
