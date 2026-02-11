hpfs_claim_dirband_alloc(struct super_block *s, secno sec)
{
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_free_dnodes != (unsigned)-1) {
		if (unlikely(!sbi->sb_n_free_dnodes)) {
			hpfs_error(s, "dirband free count underflow, allocating sector %08x", sec);
			sbi->sb_n_free_dnodes = -1;
			return;
		}
		sbi->sb_n_free_dnodes--;
	}
}
