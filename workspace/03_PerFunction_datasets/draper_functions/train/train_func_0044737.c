shmem_put_super(struct super_block *sb)
{
	struct shmem_sb_info *sbinfo = SHMEM_SB(sb);

	if (!sbinfo->idr_nouse)
		idr_destroy(&sbinfo->idr);
	percpu_counter_destroy(&sbinfo->used_blocks);
	mpol_put(sbinfo->mpol);
	kfree(sbinfo);
	sb->s_fs_info = NULL;
}
