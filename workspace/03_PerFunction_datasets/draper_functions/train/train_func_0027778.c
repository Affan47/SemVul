au_h_iptr(struct inode *inode, aufs_bindex_t bindex)
{
	struct inode *h_inode;

	IiMustAnyLock(inode);

	h_inode = au_ii(inode)->ii_hinode[0 + bindex].hi_inode;
	AuDebugOn(h_inode && atomic_read(&h_inode->i_count) <= 0);
	return h_inode;
}
