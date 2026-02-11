ParseIdent()
{
	const char* reset = _src;


	char firstChar = *_src;
	if('"' != firstChar)
	{
		if(firstChar == 't' || firstChar == 'f' || firstChar == 'n')
		{
			const char* chars = "truefalsnu";
			int len = strspn(_src, chars);


			RESERVED("true", TOKEN_TRUE);
			RESERVED("false", TOKEN_FALSE);
			RESERVED("null", TOKEN_NULL);
		}

		return false;
	}
	++_src;


	int nLines = 0;
	const char* ptr;
	bool escaped = false;
	for(ptr = _src; ptr != 0; ++ptr)
	{
		char c = *ptr;
		if(isprint(c) || (isspace(c) && '\v' != c) || '\b' == c)
		{
			if('\\' == c && !escaped)
			{
				char n = *(ptr+1);
				if('"' != n && '\\' != n && '/' != n && 'b' != n && 'f' != n && 'n' != n && 'r' != n && 't' != n)
				{
					_src = reset;
					return false;
				}
				else
				{
					escaped = true;
					continue;
				}
			}
			else if('"' == c && !escaped)
			{

				break;
			}
			else if('n' == c && escaped)
			{
				++nLines;
			}
		}
		else
		{
			_src = reset;
			return false;
		}

		escaped = false;
	}

	if(0 == *ptr)
	{
		_src = reset;
		return false;
	}

	int len = ptr - _src;

	_line += nLines;
	_data = LJString(_src, len);
	_data = UnEscape(_data);
	_src += len+1;
	_token = TOKEN_STRING;

	return true;
}
