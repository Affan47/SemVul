Devices_IsValidForFilename(char ch)
{
	if ((ch >= 'A' && ch <= 'Z')
	 || (ch >= 'a' && ch <= 'z')
	 || (ch >= '0' && ch <= '9'))
		return TRUE;
	switch (ch) {
	case '!':
	case '#':
	case '$':
	case '&':
	case '\'':
	case '(':
	case ')':
	case '*':
	case '-':
	case '.':
	case '?':
	case '@':
	case '_':
		return TRUE;
	default:
		return FALSE;
	}
}
