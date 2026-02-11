smack_sb_alloc_security(struct super_block *sb)
{
	struct superblock_smack *sbsp;

	sbsp = kzalloc(sizeof(struct superblock_smack), GFP_KERNEL);

	if (sbsp == NULL)
		return -ENOMEM;

	sbsp->smk_root = &smack_known_floor;
	sbsp->smk_default = &smack_known_floor;
	sbsp->smk_floor = &smack_known_floor;
	sbsp->smk_hat = &smack_known_hat;


	sb->s_security = sbsp;

	return 0;
}
