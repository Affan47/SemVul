printSum(const unsigned char *p)
{
	int i;

	for (i = 0; i < 16; ++i)
		printf("%02x", *p++);
}
