ima_fix_xattr(struct dentry *dentry,
			 struct integrity_iint_cache *iint)
{
	int rc, offset;
	u8 algo = iint->ima_hash->algo;

	if (algo <= HASH_ALGO_SHA1) {
		offset = 1;
		iint->ima_hash->xattr.sha1.type = IMA_XATTR_DIGEST;
	} else {
		offset = 0;
		iint->ima_hash->xattr.ng.type = IMA_XATTR_DIGEST_NG;
		iint->ima_hash->xattr.ng.algo = algo;
	}
	rc = __vfs_setxattr_noperm(dentry, XATTR_NAME_IMA,
				   &iint->ima_hash->xattr.data[offset],
				   (sizeof(iint->ima_hash->xattr) - offset) +
				   iint->ima_hash->length, 0);
	return rc;
}
