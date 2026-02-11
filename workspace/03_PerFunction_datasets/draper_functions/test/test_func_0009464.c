interleave_bits(struct interleave *s, unsigned int *bits)
{
	unsigned char *syms;
	int i;

	syms = g_alloca(s->size * sizeof(unsigned char));

	for (i = 0; i < s->size; i++)
		syms[i] = (*bits >> (s->size - i - 1)) & 1;

	interleave_syms(s, syms);

	for (*bits = i = 0; i < s->size; i++)
		*bits = (*bits << 1) | syms[i];
}
