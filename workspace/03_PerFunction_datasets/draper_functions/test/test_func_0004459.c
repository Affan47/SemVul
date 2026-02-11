canMatch (const unsigned char** s, const char* literal)
{
	const int literal_length = strlen (literal);
	const unsigned char next_char = *(*s + literal_length);
	if (strncmp ((const char*) *s, literal, literal_length) != 0)
	{
	    return FALSE;
	}

	if ( ! (next_char == 0 || isspace (next_char) || next_char == '(' || next_char == ';'))
	{
	    return FALSE;
	}
	*s += literal_length;
	return TRUE;
}
