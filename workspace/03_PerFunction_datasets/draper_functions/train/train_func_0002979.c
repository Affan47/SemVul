fai_destroy(faidx_t *fai)
{
	int i;
	for (i = 0; i < fai->n; ++i) free(fai->name[i]);
	free(fai->name);
	kh_destroy(s, fai->hash);
	if (fai->rz) razf_close(fai->rz);
	free(fai);
}
