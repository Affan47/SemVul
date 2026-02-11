f2fs_fname_encrypt(struct inode *inode,
			const struct qstr *iname, struct f2fs_str *oname)
{
	u32 ciphertext_len;
	struct ablkcipher_request *req = NULL;
	DECLARE_F2FS_COMPLETION_RESULT(ecr);
	struct f2fs_crypt_info *ci = F2FS_I(inode)->i_crypt_info;
	struct crypto_ablkcipher *tfm = ci->ci_ctfm;
	int res = 0;
	char iv[F2FS_CRYPTO_BLOCK_SIZE];
	struct scatterlist src_sg, dst_sg;
	int padding = 4 << (ci->ci_flags & F2FS_POLICY_FLAGS_PAD_MASK);
	char *workbuf, buf[32], *alloc_buf = NULL;
	unsigned lim = max_name_len(inode);

	if (iname->len <= 0 || iname->len > lim)
		return -EIO;

	ciphertext_len = (iname->len < F2FS_CRYPTO_BLOCK_SIZE) ?
		F2FS_CRYPTO_BLOCK_SIZE : iname->len;
	ciphertext_len = f2fs_fname_crypto_round_up(ciphertext_len, padding);
	ciphertext_len = (ciphertext_len > lim) ? lim : ciphertext_len;

	if (ciphertext_len <= sizeof(buf)) {
		workbuf = buf;
	} else {
		alloc_buf = kmalloc(ciphertext_len, GFP_NOFS);
		if (!alloc_buf)
			return -ENOMEM;
		workbuf = alloc_buf;
	}


	req = ablkcipher_request_alloc(tfm, GFP_NOFS);
	if (!req) {
		printk_ratelimited(KERN_ERR
			"%s: crypto_request_alloc() failed\n", __func__);
		kfree(alloc_buf);
		return -ENOMEM;
	}
	ablkcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			f2fs_dir_crypt_complete, &ecr);


	memcpy(workbuf, iname->name, iname->len);
	if (iname->len < ciphertext_len)
		memset(workbuf + iname->len, 0, ciphertext_len - iname->len);


	memset(iv, 0, F2FS_CRYPTO_BLOCK_SIZE);


	sg_init_one(&src_sg, workbuf, ciphertext_len);
	sg_init_one(&dst_sg, oname->name, ciphertext_len);
	ablkcipher_request_set_crypt(req, &src_sg, &dst_sg, ciphertext_len, iv);
	res = crypto_ablkcipher_encrypt(req);
	if (res == -EINPROGRESS || res == -EBUSY) {
		wait_for_completion(&ecr.completion);
		res = ecr.res;
	}
	kfree(alloc_buf);
	ablkcipher_request_free(req);
	if (res < 0) {
		printk_ratelimited(KERN_ERR
				"%s: Error (error code %d)\n", __func__, res);
	}
	oname->len = ciphertext_len;
	return res;
}
