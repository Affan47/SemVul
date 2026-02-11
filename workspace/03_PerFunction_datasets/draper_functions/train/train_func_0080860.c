parseImplicitPartStmt (tokenInfo *const token)
{
	boolean result = TRUE;
	switch (token->keyword)
	{
		case KEYWORD_entry: parseEntryStmt (token); break;

		case KEYWORD_implicit:
		case KEYWORD_include:
		case KEYWORD_parameter:
		case KEYWORD_format:
			skipToNextStatement (token);
			break;

		default: result = FALSE; break;
	}
	return result;
}
