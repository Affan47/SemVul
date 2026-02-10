toKeyword(Scanner *s)
{
	std::string t="";

	if ( s->match ( "appbar_color_to" ) )
	{
		t = "{";

		if ( s->match ( t ) )
		{
			rgbKeywords(s);
			to.red = temp_color;

			rgbKeywords(s);
			to.green = temp_color;

			rgbKeywords(s);
			to.blue = temp_color;

			t = "}";

			if ( s->match ( t ) )
			{
				return true;
			}
		}

	}

	return false;
}
