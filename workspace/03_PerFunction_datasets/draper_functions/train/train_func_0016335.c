sfsfindblock (struct adfhandle *adf, int btree, int theblock, struct sfsblock **sfsb, int *sfsblockcnt, int *sfsmaxblockcnt, int sfs2)
{
	int nodecount, isleaf, nodesize;
	int i;
	uae_u8 *p;

	if (!btree)
		return 0;
	if (!adf_read_block (adf, btree))
		return 0;
	if (memcmp (adf->block, "BNDC", 4))
		return 0;
	nodecount = gwx (adf->block + 12);
	isleaf = adf->block[14];
	nodesize = adf->block[15];
	p = adf->block + 16;
	for (i = 0; i < nodecount; i++) {
		if (isleaf) {
			uae_u32 key = glx (p);
			uae_u32 next = glx (p + 4);
			uae_u32 prev = glx (p + 8);
			uae_u32 blocks;
			if (sfs2)
				blocks = glx (p + 12);
			else
				blocks = gwx (p + 12);
			if (key == theblock) {
				struct sfsblock *sb;
				if (*sfsblockcnt >= *sfsmaxblockcnt) {
					*sfsmaxblockcnt += 100;
					*sfsb = xrealloc (struct sfsblock, *sfsb, *sfsmaxblockcnt);
				}
				sb = *sfsb + (*sfsblockcnt);
				sb->block = key;
				sb->length = blocks;
				(*sfsblockcnt)++;
				return next;
			}
		} else {
			uae_u32 key = glx (p);
			uae_u32 data = glx (p + 4);
			int newblock = sfsfindblock (adf, data, theblock, sfsb, sfsblockcnt, sfsmaxblockcnt, sfs2);
			if (newblock)
				return newblock;
			if (!adf_read_block (adf, btree))
				return 0;
			if (memcmp (adf->block, "BNDC", 4))
				return 0;
		}
		p += nodesize;
	}
	return 0;
}
