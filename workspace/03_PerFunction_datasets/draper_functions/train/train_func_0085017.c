rando(size_t n)
{
	long ran;
	long limit = RAND_MAX - (RAND_MAX % (long)n);
	if(n<2) return 0;
	do{ ran = RAND(); }while( ran >= limit );
	return (size_t)(ran%n);
}
