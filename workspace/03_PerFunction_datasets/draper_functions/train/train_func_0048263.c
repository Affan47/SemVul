ecryptfs_i_size_read(struct dentry *dentry, struct inode *inode)
{
	struct ecryptfs_crypt_stat *crypt_stat;
	int rc;

	rc = ecryptfs_get_lower_file(dentry, inode);
	if (rc) {
		printk(KERN_ERR "%s: Error attempting to initialize "
			"the lower file for the dentry with name "
			"[%pd]; rc = [%d]\n", __func__,
			dentry, rc);
		return rc;
	}

	crypt_stat = &ecryptfs_inode_to_private(inode)->crypt_stat;

	if (!(crypt_stat->flags & ECRYPTFS_POLICY_APPLIED))
		ecryptfs_set_default_sizes(crypt_stat);

	rc = ecryptfs_read_and_validate_header_region(inode);
	ecryptfs_put_lower_file(inode);
	if (rc) {
		rc = ecryptfs_read_and_validate_xattr_region(dentry, inode);
		if (!rc)
			crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
	}


	return 0;
}
