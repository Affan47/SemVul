asc2int(c)
int c;
{
	if (c < 0) return(-1);
	else if (Xisdigit(c)) return(c - '0');
	else if (Xislower(c)) return(c - 'a' + 10);
	else if (Xisupper(c)) return(c - 'A' + 10);

	return(-1);
}
