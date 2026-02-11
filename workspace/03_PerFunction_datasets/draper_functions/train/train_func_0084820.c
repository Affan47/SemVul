charName(int ch)
{
	if (ch == EOF)
		return "EOF";
	else
	{
		ANTLR_USE_NAMESPACE(std)string s;


		ch = ch & 0xFF;
#ifdef ANTLR_CCTYPE_NEEDS_STD
		if( ANTLR_USE_NAMESPACE(std)isprint( ch ) )
#else
		if( isprint( ch ) )
#endif
		{
			s.append("'");
			s += ch;
			s.append("'");

		}
		else
		{
			s += "0x";

			unsigned int t = ch >> 4;
			if( t < 10 )
				s += t | 0x30;
			else
				s += t + 0x37;
			t = ch & 0xF;
			if( t < 10 )
				s += t | 0x30;
			else
				s += t + 0x37;
		}
		return s;
	}
}
