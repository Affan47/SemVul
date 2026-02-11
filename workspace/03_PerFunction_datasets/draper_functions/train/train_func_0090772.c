security_inode_init_security(struct inode *inode, struct inode *dir,
				 const struct qstr *qstr,
				 const initxattrs initxattrs, void *fs_data)
{
	struct xattr new_xattrs[MAX_LSM_EVM_XATTR + 1];
	struct xattr *lsm_xattr, *evm_xattr, *xattr;
	int ret;

	if (unlikely(IS_PRIVATE(inode)))
		return 0;

	if (!initxattrs)
		return call_int_hook(inode_init_security, -EOPNOTSUPP, inode,
				     dir, qstr, NULL, NULL, NULL);
	memset(new_xattrs, 0, sizeof(new_xattrs));
	lsm_xattr = new_xattrs;
	ret = call_int_hook(inode_init_security, -EOPNOTSUPP, inode, dir, qstr,
						&lsm_xattr->name,
						&lsm_xattr->value,
						&lsm_xattr->value_len);
	if (ret)
		goto out;

	evm_xattr = lsm_xattr + 1;
	ret = evm_inode_init_security(inode, lsm_xattr, evm_xattr);
	if (ret)
		goto out;
	ret = initxattrs(inode, new_xattrs, fs_data);
out:
	for (xattr = new_xattrs; xattr->value != NULL; xattr++)
		kfree(xattr->value);
	return (ret == -EOPNOTSUPP) ? 0 : ret;
}
