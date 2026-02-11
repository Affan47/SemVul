pnfs_layout_io_set_failed(struct pnfs_layout_hdr *lo, u32 iomode)
{
	struct inode *inode = lo->plh_inode;
	struct pnfs_layout_range range = {
		.iomode = iomode,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	};
	LIST_HEAD(head);

	spin_lock(&inode->i_lock);
	pnfs_layout_set_fail_bit(lo, pnfs_iomode_to_fail_bit(iomode));
	pnfs_mark_matching_lsegs_invalid(lo, &head, &range);
	spin_unlock(&inode->i_lock);
	pnfs_free_lseg_list(&head);
	dprintk("%s Setting layout IOMODE_%s fail bit\n", __func__,
			iomode == IOMODE_RW ?  "RW" : "READ");
}
