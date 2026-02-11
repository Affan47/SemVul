encodeURL(String &str, char *valid)
{
    String	temp;
    static char	*digits = "0123456789ABCDEF";
    char	*p;

    for (p = str; p && *p; p++)
    {
	if (isascii(*p) && (isdigit(*p) || isalpha(*p) || strchr(valid, *p)))
	    temp << *p;
	else
	{
	    temp << '%';
	    temp << digits[(*p >> 4) & 0x0f];
	    temp << digits[*p & 0x0f];
	}
    }
    str = temp;
    return (str);
}
