isDPostArgumentToken(tokenInfo *const token)
{
	switch (token->keyword)
	{


		case KEYWORD_CONST:

		case KEYWORD_IF:

		case KEYWORD_IN:
		case KEYWORD_OUT:
		case KEYWORD_BODY:
			return TRUE;
		default:
			break;
	}

	if (vStringValue(token->name)[0] == '@')
		return TRUE;
	return FALSE;
}
