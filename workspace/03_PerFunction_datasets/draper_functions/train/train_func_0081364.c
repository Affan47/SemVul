SetLetterBits(Translator *tr, int group, const char *string)
{
	int bits;
	unsigned char c;

	bits = (1L << group);
	while((c = *string++) != 0)
		tr->letter_bits[c] |= bits;
}
