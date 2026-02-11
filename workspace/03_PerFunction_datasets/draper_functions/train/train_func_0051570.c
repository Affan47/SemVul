ucs2chr(const ucs2_char_t* string, ucs2_char_t c)
{
	ucs2_char_t* ret = 0;
	while (*string) {
		if (*string == c)	{
			ret = (ucs2_char_t*)string;
			break;
		}
		string++;
	}
	return ret;
}
