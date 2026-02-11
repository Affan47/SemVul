getmbi(int (*getin) (void *in), void *in)
{
	int i, mbi = 0;

	do {
		i = getin(in);
		if(i < 0) {
			return (-1);
		}
		mbi = (mbi << 7) | (i & 0x7f);
	} while(i & 0x80);

	return mbi;
}
