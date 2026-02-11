eputc(struct MF *mf, unsigned char c)
{
	int return_val;

	if ((mf->Mf_putc) == NULLFUNC) {
		mferror(mf, "Mf_putc undefined");
		return (-1);
	}

	return_val = (mf->Mf_putc) (mf, c);

	if (return_val == EOF)
		mferror(mf, "error writing");

	mf->Mf_numbyteswritten++;
	return (return_val);
}
