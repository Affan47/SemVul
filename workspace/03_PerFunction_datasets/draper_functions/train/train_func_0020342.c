xfs_xattr_prefix(int flags)
{
	if (flags & XFS_ATTR_SECURE)
		return xfs_xattr_security_handler.prefix;
	else if (flags & XFS_ATTR_ROOT)
		return xfs_xattr_trusted_handler.prefix;
	else
		return xfs_xattr_user_handler.prefix;
}
