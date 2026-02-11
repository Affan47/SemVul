cleanse(char buf[], int n)
{
    while (--n >= 0)
	if (!isprint(buf[n]) && !isspace(buf[n]))
	    buf[n] = '?';
}
