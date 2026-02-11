pnfs_list_write_lseg_done(struct inode *inode, struct list_head *listp)
{
	struct pnfs_layout_segment *lseg, *tmp;


	list_for_each_entry_safe(lseg, tmp, listp, pls_lc_list) {
		list_del_init(&lseg->pls_lc_list);
		pnfs_put_lseg(lseg);
	}

	pnfs_clear_layoutcommitting(inode);
}
