pdf_code_from_string(char *buf, int len)
{
	int a = 0;
	while (len--)
		a = (a << 8) | *(unsigned char *)buf++;
	return a;
}
