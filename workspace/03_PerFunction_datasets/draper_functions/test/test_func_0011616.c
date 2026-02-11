sysv_nblocks(struct super_block *s, loff_t size)
{
	struct sysv_sb_info *sbi = SYSV_SB(s);
	int ptrs_bits = sbi->s_ind_per_block_bits;
	unsigned blocks, res, direct = DIRECT, i = DEPTH;
	blocks = (size + s->s_blocksize - 1) >> s->s_blocksize_bits;
	res = blocks;
	while (--i && blocks > direct) {
		blocks = ((blocks - direct - 1) >> ptrs_bits) + 1;
		res += blocks;
		direct = 1;
	}
	return blocks;
}
