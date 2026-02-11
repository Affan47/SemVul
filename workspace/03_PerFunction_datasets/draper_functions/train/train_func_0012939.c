HandleString( unsigned int & cur, unsigned int one_too_much, Accessor & styler )
{
	char ch;


	bool even_backslash_count = true;
	cur++;
	for( ; ; )
	{
		if( cur >= one_too_much )
		{
			styler.ColourTo( cur - 1, SCE_OPAL_STRING );
			return false;
		}

		ch = styler.SafeGetCharAt( cur );
		if( ( ch == '\015' ) || ( ch == '\012' ) )
		{
			styler.ColourTo( cur - 1, SCE_OPAL_STRING );
			styler.StartSegment( cur );
			return true;
		}
		else
		{
			if( even_backslash_count )
			{
				if( ch == '"' )
				{
					styler.ColourTo( cur, SCE_OPAL_STRING );
					cur++;
					if( cur >= one_too_much )
					{
						return false;
					}
					else
					{
						styler.StartSegment( cur );
						return true;
					}
				}
				else if( ch == '\\' )
				{
					even_backslash_count = false;
				}
			}
			else
			{
				even_backslash_count = true;
			}
		}

		cur++;
	}
}
