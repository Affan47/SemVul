_is_punct(int c)
{
	return ((c > 32) && (c < 128) && !(_is_letter(c) || _is_digit(c)));
}
