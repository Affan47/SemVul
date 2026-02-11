bcf_destroy(bcf1_t *b)
{
	int i;
	if (b == 0) return -1;
	free(b->str);
	for (i = 0; i < b->m_gi; ++i)
		free(b->gi[i].data);
	free(b->gi);
	free(b);
	return 0;
}
