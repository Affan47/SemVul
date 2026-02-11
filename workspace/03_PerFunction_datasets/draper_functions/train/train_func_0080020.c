parseExecutionPart (tokenInfo *const token)
{
	boolean result = FALSE;
	boolean done = FALSE;
	while (! done)
	{
		switch (token->keyword)
		{
			default:
				if (isSubprogramPrefix (token))
					readToken (token);
				else
					skipToNextStatement (token);
				result = TRUE;
				break;

			case KEYWORD_entry:
				parseEntryStmt (token);
				result = TRUE;
				break;

			case KEYWORD_contains:
			case KEYWORD_function:
			case KEYWORD_subroutine:
				done = TRUE;
				break;

			case KEYWORD_end:
				readSubToken (token);
				if (isSecondaryKeyword (token, KEYWORD_do) ||
					isSecondaryKeyword (token, KEYWORD_if) ||
					isSecondaryKeyword (token, KEYWORD_select) ||
					isSecondaryKeyword (token, KEYWORD_where))
				{
					skipToNextStatement (token);
					result = TRUE;
				}
				else
					done = TRUE;
				break;
		}
	}
	return result;
}
