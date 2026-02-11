init_xattrs(struct inode *inode, const struct xattr *xattr_array,
		      void *fs_info)
{
	const struct xattr *xattr;
	char *name;
	int err = 0;

	for (xattr = xattr_array; xattr->name != NULL; xattr++) {
		name = kmalloc(XATTR_SECURITY_PREFIX_LEN +
			       strlen(xattr->name) + 1, GFP_NOFS);
		if (!name) {
			err = -ENOMEM;
			break;
		}
		strcpy(name, XATTR_SECURITY_PREFIX);
		strcpy(name + XATTR_SECURITY_PREFIX_LEN, xattr->name);
		err = setxattr(inode, name, xattr->value, xattr->value_len, 0);
		kfree(name);
		if (err < 0)
			break;
	}

	return err;
}
