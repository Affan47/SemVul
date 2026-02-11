skipPostArgumentStuff (
		statementInfo *const st, parenInfo *const info)
{
	tokenInfo *const token = activeToken (st);
	unsigned int parameters = info->parameterCount;
	unsigned int elementCount = 0;
	boolean restart = FALSE;
	boolean end = FALSE;
	int c = skipToNonWhite ();

	do
	{
		switch (c)
		{
		case ')':                               break;
		case ':': skipMemIntializerList (token);break;
		case '[': skipToMatch ("[]");           break;
		case '=': cppUngetc (c); end = TRUE;    break;
		case '{': cppUngetc (c); end = TRUE;    break;
		case '}': cppUngetc (c); end = TRUE;    break;

		case '(':
			if (elementCount > 0)
				++elementCount;
			skipToMatch ("()");
			break;

		case ';':
			if (parameters == 0  ||  elementCount < 2)
			{
				cppUngetc (c);
				end = TRUE;
			}
			else if (--parameters == 0)
				end = TRUE;
			break;

		default:
			if (isident1 (c))
			{
				readIdentifier (token, c);
				switch (token->keyword)
				{
				case KEYWORD_ATTRIBUTE: skipParens ();  break;
				case KEYWORD_THROW:     skipParens ();  break;
				case KEYWORD_TRY:                       break;

				case KEYWORD_CONST:
				case KEYWORD_VOLATILE:
					if (vStringLength (Signature) > 0)
					{
						vStringPut (Signature, ' ');
						vStringCat (Signature, token->name);
					}
					break;

				case KEYWORD_CATCH:
				case KEYWORD_CLASS:
				case KEYWORD_EXPLICIT:
				case KEYWORD_EXTERN:
				case KEYWORD_FRIEND:
				case KEYWORD_INLINE:
				case KEYWORD_MUTABLE:
				case KEYWORD_NAMESPACE:
				case KEYWORD_NEW:
				case KEYWORD_NEWCOV:
				case KEYWORD_OPERATOR:
				case KEYWORD_OVERLOAD:
				case KEYWORD_PRIVATE:
				case KEYWORD_PROTECTED:
				case KEYWORD_PUBLIC:
				case KEYWORD_STATIC:
				case KEYWORD_TEMPLATE:
				case KEYWORD_TYPEDEF:
				case KEYWORD_TYPENAME:
				case KEYWORD_USING:
				case KEYWORD_VIRTUAL:

					restart = TRUE;
					end = TRUE;
					break;

				default:
					if (isType (token, TOKEN_NONE))
						;
					else if (info->isKnrParamList  &&  info->parameterCount > 0)
						++elementCount;
					else
					{


						restart = TRUE;
						end = TRUE;
					}
					break;
				}
			}
		}
		if (! end)
		{
			c = skipToNonWhite ();
			if (c == EOF)
				end = TRUE;
		}
	} while (! end);

	if (restart)
		restartStatement (st);
	else
		setToken (st, TOKEN_NONE);

	return (boolean) (c != EOF);
}
