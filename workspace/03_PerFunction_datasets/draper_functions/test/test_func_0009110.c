__hfs_ext_write_extent(struct inode *inode, struct hfs_find_data *fd)
{
	int res;

	hfs_ext_build_key(fd->search_key, inode->i_ino, HFS_I(inode)->cached_start,
			  HFS_IS_RSRC(inode) ?  HFS_FK_RSRC : HFS_FK_DATA);
	res = hfs_brec_find(fd);
	if (HFS_I(inode)->flags & HFS_FLG_EXT_NEW) {
		if (res != -ENOENT)
			return res;
		hfs_brec_insert(fd, HFS_I(inode)->cached_extents, sizeof(hfs_extent_rec));
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_DIRTY|HFS_FLG_EXT_NEW);
	} else {
		if (res)
			return res;
		hfs_bnode_write(fd->bnode, HFS_I(inode)->cached_extents, fd->entryoffset, fd->entrylength);
		HFS_I(inode)->flags &= ~HFS_FLG_EXT_DIRTY;
	}
	return 0;
}
