eputc(c)
unsigned char c;
{
	int return_val;

	if((Mf_putc) == NULLFUNC)
	{
		mferror("Mf_putc undefined");
		return(-1);
	}

	return_val = (Mf_putc)(c);

	if ( return_val == EOF )
		mferror("error writing");

	Mf_numbyteswritten++;
	return(return_val);
}
