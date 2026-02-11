xfs_mount (void)
{
	xfs_sb_t super;

	if (!devread (0, 0, sizeof(super), (char *)&super)
	    || (le32(super.sb_magicnum) != XFS_SB_MAGIC)
	    || ((le16(super.sb_versionnum)
		& XFS_SB_VERSION_NUMBITS) != XFS_SB_VERSION_4) ) {
		return 0;
	}

	xfs.bsize = le32 (super.sb_blocksize);
	xfs.blklog = super.sb_blocklog;
	xfs.bdlog = xfs.blklog - SECTOR_BITS;
	xfs.rootino = le64 (super.sb_rootino);
	xfs.isize = le16 (super.sb_inodesize);
	xfs.agblocks = le32 (super.sb_agblocks);
	xfs.dirbsize = xfs.bsize << super.sb_dirblklog;

	xfs.inopblog = super.sb_inopblog;
	xfs.agblklog = super.sb_agblklog;
	xfs.agnolog = xfs_highbit32 (le32(super.sb_agcount));

	xfs.btnode_ptr0_off =
		((xfs.bsize - sizeof(xfs_btree_block_t)) /
		(sizeof (xfs_bmbt_key_t) + sizeof (xfs_bmbt_ptr_t)))
		 * sizeof(xfs_bmbt_key_t) + sizeof(xfs_btree_block_t);

	return 1;
}
