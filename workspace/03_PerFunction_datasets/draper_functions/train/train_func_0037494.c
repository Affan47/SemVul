init_extents (void)
{
	xfs_bmbt_ptr_t ptr0;
	xfs_btree_lblock_t h;

	switch (icore.di_format) {
	case XFS_DINODE_FMT_EXTENTS:
		xfs.xt = inode->di_u.di_bmx;
		xfs.nextents = le32 (icore.di_nextents);
		break;
	case XFS_DINODE_FMT_BTREE:
		ptr0 = xfs.ptr0;
		for (;;) {
			xfs.daddr = fsb2daddr (le64(ptr0));
			devread (xfs.daddr, 0,
				 sizeof(xfs_btree_lblock_t), (char *)&h);
			if (!h.bb_level) {
				xfs.nextents = le16(h.bb_numrecs);
				xfs.next = fsb2daddr (le64(h.bb_rightsib));
				xfs.fpos = sizeof(xfs_btree_block_t);
				return;
			}
			devread (xfs.daddr, xfs.btnode_ptr0_off,
				 sizeof(xfs_bmbt_ptr_t), (char *)&ptr0);
		}
	}
}
