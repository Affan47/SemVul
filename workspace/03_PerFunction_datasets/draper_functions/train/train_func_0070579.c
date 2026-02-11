symlink_hash(unsigned int link_len, const char *link_str, u8 *md5_hash)
{
	int rc;
	unsigned int size;
	struct crypto_shash *md5;
	struct sdesc *sdescmd5;

	md5 = crypto_alloc_shash("md5", 0, 0);
	if (IS_ERR(md5)) {
		rc = PTR_ERR(md5);
		cifs_dbg(VFS, "%s: Crypto md5 allocation error %d\n",
			 __func__, rc);
		return rc;
	}
	size = sizeof(struct shash_desc) + crypto_shash_descsize(md5);
	sdescmd5 = kmalloc(size, GFP_KERNEL);
	if (!sdescmd5) {
		rc = -ENOMEM;
		goto symlink_hash_err;
	}
	sdescmd5->shash.tfm = md5;
	sdescmd5->shash.flags = 0x0;

	rc = crypto_shash_init(&sdescmd5->shash);
	if (rc) {
		cifs_dbg(VFS, "%s: Could not init md5 shash\n", __func__);
		goto symlink_hash_err;
	}
	rc = crypto_shash_update(&sdescmd5->shash, link_str, link_len);
	if (rc) {
		cifs_dbg(VFS, "%s: Could not update with link_str\n", __func__);
		goto symlink_hash_err;
	}
	rc = crypto_shash_final(&sdescmd5->shash, md5_hash);
	if (rc)
		cifs_dbg(VFS, "%s: Could not generate md5 hash\n", __func__);

symlink_hash_err:
	crypto_free_shash(md5);
	kfree(sdescmd5);

	return rc;
}
