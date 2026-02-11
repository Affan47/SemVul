nilfs_segctor_begin_finfo(struct nilfs_sc_info *sci,
				      struct inode *inode)
{
	sci->sc_curseg->sb_sum.nfinfo++;
	sci->sc_binfo_ptr = sci->sc_finfo_ptr;
	nilfs_segctor_map_segsum_entry(
		sci, &sci->sc_binfo_ptr, sizeof(struct nilfs_finfo));

	if (NILFS_I(inode)->i_root &&
	    !test_bit(NILFS_SC_HAVE_DELTA, &sci->sc_flags))
		set_bit(NILFS_SC_HAVE_DELTA, &sci->sc_flags);

}
