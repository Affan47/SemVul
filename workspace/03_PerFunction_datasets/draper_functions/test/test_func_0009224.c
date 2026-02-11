pos(char c)
{
    const char *p;
    for (p = base64_chars; *p; p++)
	if (*p == c)
	    return p - base64_chars;
    return -1;
}
