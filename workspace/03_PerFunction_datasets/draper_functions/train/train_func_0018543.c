space_test(Unicode_t ch)
{
	return IS_CODEPOINT(ch) && isspace(ch);
}
