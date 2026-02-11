readToken (tokenInfo *const token)
{
	int c;

	token->type			= TOKEN_UNDEFINED;
	token->keyword		= KEYWORD_NONE;
	vStringClear (token->string);

getNextChar:
	do
	{
		c = fileGetc ();
		token->lineNumber   = getSourceLineNumber ();
		token->filePosition = getInputFilePosition ();
	}
	while (c == '\t'  ||  c == ' ' ||  c == '\n');

	switch (c)
	{
		case EOF: longjmp (Exception, (int)ExceptionEOF);	break;
		case '(': token->type = TOKEN_OPEN_PAREN;			break;
		case ')': token->type = TOKEN_CLOSE_PAREN;			break;
		case ';': token->type = TOKEN_SEMICOLON;			break;
		case ',': token->type = TOKEN_COMMA;				break;
		case '.': token->type = TOKEN_PERIOD;				break;
		case ':': token->type = TOKEN_COLON;				break;
		case '{': token->type = TOKEN_OPEN_CURLY;			break;
		case '}': token->type = TOKEN_CLOSE_CURLY;			break;
		case '=': token->type = TOKEN_EQUAL_SIGN;			break;
		case '[': token->type = TOKEN_OPEN_SQUARE;			break;
		case ']': token->type = TOKEN_CLOSE_SQUARE;			break;
		case '?': token->type = TOKEN_QUESTION_MARK;		break;
		case '*': token->type = TOKEN_STAR;					break;

		case '\'':
		case '"':
				  token->type = TOKEN_STRING;
				  parseString (token->string, c);
				  token->lineNumber = getSourceLineNumber ();
				  token->filePosition = getInputFilePosition ();
				  break;

		case '\\':


				  c = fileGetc ();
				  if (! isalpha (c))
					  fileUngetc (c);
				  else
				  {
					  parseIdentifier (token->string, c);
					  token->lineNumber = getSourceLineNumber ();
					  token->filePosition = getInputFilePosition ();
					  token->keyword = analyzeToken (token->string, Lang_js);
					  if (isKeyword (token, KEYWORD_NONE))
						  token->type = TOKEN_IDENTIFIER;
					  else
						  token->type = TOKEN_KEYWORD;
				  }
				  break;

		case '%':
				  fileSkipToCharacter ('\n');
				  goto getNextChar;
				  break;

		default:
				  if (! isIdentChar (c))
					  token->type = TOKEN_UNDEFINED;
				  else
				  {
					  parseIdentifier (token->string, c);
					  token->lineNumber = getSourceLineNumber ();
					  token->filePosition = getInputFilePosition ();
					  token->type = TOKEN_IDENTIFIER;
				  }
				  break;
	}
}
