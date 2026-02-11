dumbfile_cgetul(DUMBFILE *f)
{
	unsigned long rv = 0;
	int v;

	do {
		v = dumbfile_getc(f);

		if (v < 0)
			return v;

		rv <<= 7;
		rv |= v & 0x7F;
	} while (v & 0x80);

	return rv;
}
