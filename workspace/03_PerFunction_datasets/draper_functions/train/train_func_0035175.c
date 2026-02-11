readIdentifier (tokenInfo *const token, const int c)
{
	parseIdentifier (token->string, c);
	token->keyword = analyzeToken (token->string, Lang_fortran);
	if (! isKeyword (token, KEYWORD_NONE))
		token->type = TOKEN_KEYWORD;
	else
	{
		token->type = TOKEN_IDENTIFIER;
		if (strncmp (vStringValue (token->string), "end", 3) == 0)
		{
			vString *const sub = vStringNewInit (vStringValue (token->string) + 3);
			const keywordId kw = analyzeToken (sub, Lang_fortran);
			vStringDelete (sub);
			if (kw != KEYWORD_NONE)
			{
				token->secondary = newToken ();
				token->secondary->type = TOKEN_KEYWORD;
				token->secondary->keyword = kw;
				token->keyword = KEYWORD_end;
			}
		}
	}
}
