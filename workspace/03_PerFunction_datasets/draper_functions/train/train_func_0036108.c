__hfs_ext_cache_extent(struct hfs_find_data *fd, struct inode *inode, u32 block)
{
	int res;

	if (HFS_I(inode)->flags & HFS_FLG_EXT_DIRTY) {
		res = __hfs_ext_write_extent(inode, fd);
		if (res)
			return res;
	}

	res = __hfs_ext_read_extent(fd, HFS_I(inode)->cached_extents, inode->i_ino,
				    block, HFS_IS_RSRC(inode) ? HFS_FK_RSRC : HFS_FK_DATA);
	if (!res) {
		HFS_I(inode)->cached_start = be16_to_cpu(fd->key->ext.FABN);
		HFS_I(inode)->cached_blocks = hfs_ext_block_count(HFS_I(inode)->cached_extents);
	} else {
		HFS_I(inode)->cached_start = HFS_I(inode)->cached_blocks = 0;
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_DIRTY|HFS_FLG_EXT_NEW);
	}
	return res;
}
