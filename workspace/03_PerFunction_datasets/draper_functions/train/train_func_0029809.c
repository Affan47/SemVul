egtb_loadindexes (tbkey_t key)
{

	unsigned long int blocksize = 1;
	unsigned long int tailblocksize1 = 0;
	unsigned long int tailblocksize2 = 0;
    unsigned long int offset=0;
	unsigned long int dummy;
	unsigned long int i;
	unsigned long int blocks;
	unsigned long int n_idx;
	unsigned long int idx;
	index_t	*p;

	bool_t ok;

	FILE *f;

	if (Uncompressed) {
		assert (decoding_scheme() == 0 && GTB_scheme == 0);
		return TRUE;
	}
	if (Zipinfo[key].blockindex != NULL)
		return TRUE;

	if (NULL == (f = egkey[key].fd))
		return FALSE;


	ok = (0 == fseek (f, 0, SEEK_SET)) &&
	fread32 (f, &dummy) &&
	fread32 (f, &dummy) &&
	fread32 (f, &blocksize) &&
	fread32 (f, &dummy) &&
	fread32 (f, &tailblocksize1) &&
	fread32 (f, &dummy) &&
	fread32 (f, &tailblocksize2) &&
	fread32 (f, &dummy) &&
	fread32 (f, &offset) &&
	fread32 (f, &dummy);

	blocks = (offset - 40)/4 -1;
	n_idx = blocks + 1;

	p = NULL;

	ok = ok && NULL != (p = (index_t *)malloc (n_idx * sizeof(index_t)));


	for (i = 0; ok && i < n_idx; i++) {
		ok = fread32 (f, &idx);
		p[i] = (index_t)idx;  assert (sizeof(index_t) >= 4);
	}

	if (ok) {
		Zipinfo[key].extraoffset = 0;
		assert (n_idx <= MAXINDEX_T);
		Zipinfo[key].totalblocks = (index_t) n_idx;
		Zipinfo[key].blockindex  = p;
	}

	if (!ok && p != NULL) {
		free(p);
	}

	return ok;
}
