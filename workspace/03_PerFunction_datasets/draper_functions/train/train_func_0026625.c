nodeTokenType(char *token, int length)
{
	NodeTag		retval;
	char	   *numptr;
	int			numlen;


	numptr = token;
	numlen = length;
	if (*numptr == '+' || *numptr == '-')
		numptr++, numlen--;
	if ((numlen > 0 && isdigit((unsigned char) *numptr)) ||
		(numlen > 1 && *numptr == '.' && isdigit((unsigned char) numptr[1])))
	{


		long		val;
		char	   *endptr;

		errno = 0;
		val = strtol(token, &endptr, 10);
		(void) val;
		if (endptr != token + length || errno == ERANGE
#ifdef HAVE_LONG_INT_64

			|| val != (long) ((int32) val)
#endif
			)
			return T_Float;
		return T_Integer;
	}


	else if (*token == '(')
		retval = LEFT_PAREN;
	else if (*token == ')')
		retval = RIGHT_PAREN;
	else if (*token == '{')
		retval = LEFT_BRACE;
	else if (*token == '\"' && length > 1 && token[length - 1] == '\"')
		retval = T_String;
	else if (*token == 'b')
		retval = T_BitString;
	else
		retval = OTHER_TOKEN;
	return retval;
}
