isIdentChar (const int c)
{
	return (boolean)
		(isalpha (c) || isdigit (c) || c == '$' ||
		  c == '_' || c == '#');
}
