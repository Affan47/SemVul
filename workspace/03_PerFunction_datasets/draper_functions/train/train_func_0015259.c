EscapeStr(const char* pstr)
{
	string _str;
	for( ; *pstr ; pstr++ )
	{
		unsigned ch = (unsigned char)*pstr;
		if( ' ' > ch  )
		{
			char hex[4];
			sprintf(hex, "\\%02x", (unsigned char)*pstr );
			_str += hex;
			pstr++;
			continue;
		}
		else if( '^' == ch || '\\' == ch )
			_str += '\\';
		_str += ch;
	}
	return _str;
}
