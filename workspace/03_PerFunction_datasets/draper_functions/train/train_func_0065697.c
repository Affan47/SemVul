lead( int32_t m )
{
	long j;
	unsigned long c = (1ul << 31);

	for(j=0; j < 32; j++)
	{
		if((c & m) != 0)
			break;
		c >>= 1;
	}
	return (j);
}
