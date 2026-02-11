ext4_mb_initialize_context(struct ext4_allocation_context *ac,
				struct ext4_allocation_request *ar)
{
	struct super_block *sb = ar->inode->i_sb;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	ext4_group_t group;
	unsigned int len;
	ext4_fsblk_t goal;
	ext4_grpblk_t block;


	len = ar->len;


	if (len >= EXT4_CLUSTERS_PER_GROUP(sb))
		len = EXT4_CLUSTERS_PER_GROUP(sb);


	goal = ar->goal;
	if (goal < le32_to_cpu(es->s_first_data_block) ||
			goal >= ext4_blocks_count(es))
		goal = le32_to_cpu(es->s_first_data_block);
	ext4_get_group_no_and_offset(sb, goal, &group, &block);


	ac->ac_b_ex.fe_logical = EXT4_LBLK_CMASK(sbi, ar->logical);
	ac->ac_status = AC_STATUS_CONTINUE;
	ac->ac_sb = sb;
	ac->ac_inode = ar->inode;
	ac->ac_o_ex.fe_logical = ac->ac_b_ex.fe_logical;
	ac->ac_o_ex.fe_group = group;
	ac->ac_o_ex.fe_start = block;
	ac->ac_o_ex.fe_len = len;
	ac->ac_g_ex = ac->ac_o_ex;
	ac->ac_flags = ar->flags;


	ext4_mb_group_or_file(ac);

	mb_debug(1, "init ac: %u blocks @ %u, goal %u, flags %x, 2^%d, "
			"left: %u/%u, right %u/%u to %swritable\n",
			(unsigned) ar->len, (unsigned) ar->logical,
			(unsigned) ar->goal, ac->ac_flags, ac->ac_2order,
			(unsigned) ar->lleft, (unsigned) ar->pleft,
			(unsigned) ar->lright, (unsigned) ar->pright,
			atomic_read(&ar->inode->i_writecount) ? "" : "non-");
	return 0;

}
