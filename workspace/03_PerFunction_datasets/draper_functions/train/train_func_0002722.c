HandleSpace( unsigned int & cur, unsigned int one_too_much, Accessor & styler )
{
	char ch;

	cur++;
	for( ; ; )
	{
		if( cur >= one_too_much )
		{
			styler.ColourTo( cur - 1, SCE_OPAL_SPACE );
			return false;
		}

		ch = styler.SafeGetCharAt( cur );
		switch( ch )
		{
		case ' ':
		case '\t':
		case '\015':
		case '\012':
			cur++;
			break;

		default:
			styler.ColourTo( cur - 1, SCE_OPAL_SPACE );
			styler.StartSegment( cur );
			return true;
		}
	}
}
