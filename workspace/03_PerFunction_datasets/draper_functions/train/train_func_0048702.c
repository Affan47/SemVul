show_hash(struct work *work, char *hashshow)
{
	unsigned char rhash[32];
	char diffdisp[16];
	unsigned long h32;
	uint32_t *hash32;
	uint64_t uintdiff;
	int ofs;

	swab256(rhash, work->hash);
	for (ofs = 0; ofs <= 28; ofs ++) {
		if (rhash[ofs])
			break;
	}
	hash32 = (uint32_t *)(rhash + ofs);
	h32 = be32toh(*hash32);
	uintdiff = round(work->work_difficulty);
	suffix_string(work->share_diff, diffdisp, sizeof (diffdisp), 0);
	snprintf(hashshow, 64, "%08lx Diff %s/%"PRIu64"%s", h32, diffdisp, uintdiff,
		 work->block? " BLOCK!" : "");
}
