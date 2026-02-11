parseLine (tokenInfo *const token, boolean is_inside_class)
{
	boolean is_terminated = TRUE;


	if (isType(token, TOKEN_KEYWORD))
	{
		switch (token->keyword)
		{
			case KEYWORD_for:
			case KEYWORD_while:
			case KEYWORD_do:
				parseLoop (token);
				break;
			case KEYWORD_if:
			case KEYWORD_else:
			case KEYWORD_try:
			case KEYWORD_catch:
			case KEYWORD_finally:

				is_terminated = parseIf (token);
				break;
			case KEYWORD_switch:
				parseSwitch (token);
				break;
			default:
				parseStatement (token, is_inside_class);
				break;
		}
	}
	else
	{


		is_terminated = parseStatement (token, is_inside_class);
	}
	return is_terminated;
}
