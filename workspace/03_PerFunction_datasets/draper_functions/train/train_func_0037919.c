compare(const String& obj) const
{
    int	len;
    int	result;
    const char	*p1 = Data;
    const char	*p2 = obj.Data;

    len = Length;
    result = 0;

    if (Length > obj.Length)
    {
	result = 1;
	len = obj.Length;
    }
    else if (Length < obj.Length)
	result = -1;

    while (len)
    {
	if (*p1 > *p2)
	    return 1;
	if (*p1 < *p2)
	    return -1;
	p1++;
	p2++;
	len--;
    }


    return result;
}
