_isDQChar(unsigned char c, bool atStart)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_')
		|| (!atStart && c >= '0' && c <= '9')
		|| (c >= (unsigned char) '\200')
		)
		return true;
	else
		return false;
}
