xfs_setattr_mode(
	struct xfs_inode	*ip,
	struct iattr		*iattr)
{
	struct inode		*inode = VFS_I(ip);
	umode_t			mode = iattr->ia_mode;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	ip->i_d.di_mode &= S_IFMT;
	ip->i_d.di_mode |= mode & ~S_IFMT;

	inode->i_mode &= S_IFMT;
	inode->i_mode |= mode & ~S_IFMT;
}
