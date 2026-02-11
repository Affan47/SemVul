hexval(char c)
{
    unsigned char uc = c | 0x20;
    unsigned int v;

    v = uc - '0';
    if (v < 10)
	return v;

    return uc - 'a' + 10;
}
