bmz8_load(FILE *f, cmph_t *mphf)
{
	cmph_uint8 nhashes;
	char *buf = NULL;
	cmph_uint32 buflen;
	cmph_uint8 i;
	register size_t nbytes;
	bmz8_data_t *bmz8 = (bmz8_data_t *)malloc(sizeof(bmz8_data_t));

	DEBUGP("Loading bmz8 mphf\n");
	mphf->data = bmz8;
	nbytes = fread(&nhashes, sizeof(cmph_uint8), (size_t)1, f);
	bmz8->hashes = (hash_state_t **)malloc(sizeof(hash_state_t *)*(size_t)(nhashes + 1));
	bmz8->hashes[nhashes] = NULL;
	DEBUGP("Reading %u hashes\n", nhashes);
	for (i = 0; i < nhashes; ++i)
	{
		hash_state_t *state = NULL;
		nbytes = fread(&buflen, sizeof(cmph_uint32), (size_t)1, f);
		DEBUGP("Hash state has %u bytes\n", buflen);
		buf = (char *)malloc((size_t)buflen);
		nbytes = fread(buf, (size_t)buflen, (size_t)1, f);
		state = hash_state_load(buf, buflen);
		bmz8->hashes[i] = state;
		free(buf);
	}

	DEBUGP("Reading m and n\n");
	nbytes = fread(&(bmz8->n), sizeof(cmph_uint8), (size_t)1, f);
	nbytes = fread(&(bmz8->m), sizeof(cmph_uint8), (size_t)1, f);

	bmz8->g = (cmph_uint8 *)malloc(sizeof(cmph_uint8)*bmz8->n);
	nbytes = fread(bmz8->g, bmz8->n*sizeof(cmph_uint8), (size_t)1, f);
	#ifdef DEBUG
	fprintf(stderr, "G: ");
	for (i = 0; i < bmz8->n; ++i) fprintf(stderr, "%u ", bmz8->g[i]);
	fprintf(stderr, "\n");
	#endif
	return;
}
