parseTypeSpec (tokenInfo *const token)
{

	Assert (isTypeSpec (token));
	switch (token->keyword)
	{
		case KEYWORD_character:

			readToken (token);
			if (isType (token, TOKEN_OPERATOR) &&
					 strcmp (vStringValue (token->string), "*") == 0)
				readToken (token);
			if (isType (token, TOKEN_PAREN_OPEN))
				skipOverParens (token);
			else if (isType (token, TOKEN_NUMERIC))
				readToken (token);
			break;


		case KEYWORD_byte:
		case KEYWORD_complex:
		case KEYWORD_integer:
		case KEYWORD_logical:
		case KEYWORD_real:
			readToken (token);
			if (isType (token, TOKEN_PAREN_OPEN))
				skipOverParens (token);
			if (isType (token, TOKEN_OPERATOR) &&
				strcmp (vStringValue (token->string), "*") == 0)
			{
				readToken (token);
				readToken (token);
			}
			break;

		case KEYWORD_double:
			readToken (token);
			if (isKeyword (token, KEYWORD_complex) ||
				isKeyword (token, KEYWORD_precision))
					readToken (token);
			else
				skipToToken (token, TOKEN_STATEMENT_END);
			break;

		case KEYWORD_record:
			readToken (token);
			if (isType (token, TOKEN_OPERATOR) &&
				strcmp (vStringValue (token->string), "/") == 0)
			{
				readToken (token);
				readToken (token);
				readToken (token);
			}
			break;

		case KEYWORD_type:
			readToken (token);
			if (isType (token, TOKEN_PAREN_OPEN))
				skipOverParens (token);
			else
				parseDerivedTypeDef (token);
			break;

		default:
			skipToToken (token, TOKEN_STATEMENT_END);
			break;
	}
}
