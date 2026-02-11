convertMnemonics(std::string & s)
{
	for (UT_uint32 i = 0; s[i] != 0; i++)
	{
		if ( s[i] == '&' ) {
			if (i > 0 && s[i-1] == '\\')
			{
				s[i-1] = '&';
                s.erase(i);
				i--;
            }
			else
				s[i] = '_';
		}
	}

    return s;
}
