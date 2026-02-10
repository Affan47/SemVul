bkread(int fi, unsigned char *buff, int size)
{
	int a, b;

	if (!size) {
		error = 0;
		return 0;
	}
	for (a = b = 0; (a < size) && ((b = joe_read(fi, buff + a, size - a)) > 0); a += b) ;
	if (b < 0)
		error = -2;
	else
		error = 0;
	return a;
}
