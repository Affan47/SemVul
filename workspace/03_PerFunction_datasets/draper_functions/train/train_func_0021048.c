parseTagHeader(FILE *f, unsigned int *typeptr, unsigned long int *lenptr)
{
	unsigned int block = getWord(f);;
	*typeptr = block >> 6;
	*lenptr = block & 63;
	if (*lenptr == 63)
		*lenptr = getDoubleWord(f);
}
