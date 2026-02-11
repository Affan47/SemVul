nilfs_segctor_fill_in_super_root(struct nilfs_sc_info *sci,
					     struct the_nilfs *nilfs)
{
	struct buffer_head *bh_sr;
	struct nilfs_super_root *raw_sr;
	unsigned isz, srsz;

	bh_sr = NILFS_LAST_SEGBUF(&sci->sc_segbufs)->sb_super_root;
	raw_sr = (struct nilfs_super_root *)bh_sr->b_data;
	isz = nilfs->ns_inode_size;
	srsz = NILFS_SR_BYTES(isz);

	raw_sr->sr_bytes = cpu_to_le16(srsz);
	raw_sr->sr_nongc_ctime
		= cpu_to_le64(nilfs_doing_gc() ?
			      nilfs->ns_nongc_ctime : sci->sc_seg_ctime);
	raw_sr->sr_flags = 0;

	nilfs_write_inode_common(nilfs->ns_dat, (void *)raw_sr +
				 NILFS_SR_DAT_OFFSET(isz), 1);
	nilfs_write_inode_common(nilfs->ns_cpfile, (void *)raw_sr +
				 NILFS_SR_CPFILE_OFFSET(isz), 1);
	nilfs_write_inode_common(nilfs->ns_sufile, (void *)raw_sr +
				 NILFS_SR_SUFILE_OFFSET(isz), 1);
	memset((void *)raw_sr + srsz, 0, nilfs->ns_blocksize - srsz);
}
