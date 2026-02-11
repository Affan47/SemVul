hpfs_claim_dirband_free(struct super_block *s, secno sec)
{
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_free_dnodes != (unsigned)-1) {
		if (unlikely(sbi->sb_n_free_dnodes >= sbi->sb_dirband_size / 4)) {
			hpfs_error(s, "dirband free count overflow, freeing sector %08x", sec);
			sbi->sb_n_free_dnodes = -1;
			return;
		}
		sbi->sb_n_free_dnodes++;
	}
}
