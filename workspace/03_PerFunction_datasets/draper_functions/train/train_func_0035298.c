blockmap_set_as_data(struct gfs2_inode *ip, uint64_t block)
{
	int error;
	struct gfs2_buffer_head *bh;
	struct gfs2_dinode *di;

	error = fsck_blkmap_set_noino(ip, block, _("data"),  gfs2_block_used);
	if (!error)
		return 0;

	error = 0;


	bh = bread(ip->i_sbd, block);
	if (gfs2_check_meta(bh, GFS2_METATYPE_DI) != 0)
		goto out;


	di = (struct gfs2_dinode *)bh->b_data;
	if (be64_to_cpu(di->di_num.no_addr) != block)
		goto out;

	log_err(_("Inode %lld (0x%llx) has a reference to block %lld (0x%llx) "
		  "as a data block, but it appears to be a dinode we "
		  "haven't checked yet.\n"),
		(unsigned long long)ip->i_di.di_num.no_addr,
		(unsigned long long)ip->i_di.di_num.no_addr,
		(unsigned long long)block, (unsigned long long)block);
	error = -1;
out:
	if (!error)
		fsck_blockmap_set(ip, block, _("data"),  gfs2_block_used);
	brelse(bh);
	return error;
}
