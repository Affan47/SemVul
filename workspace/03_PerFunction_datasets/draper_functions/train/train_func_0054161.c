sig_dio24_suspend(struct sig_dio24 *b, FILE *fSig)
{
	int i;
	size_t size = sizeof(*b);

	generic_suspend(b, size, fSig);

	for (i = 0; i < 24; i++) {
		sig_std_logic_suspend(b->sig[i], fSig);
	}
}
