pefile_digest_pe(const void *pebuf, unsigned int pelen,
			    struct pefile_context *ctx)
{
	struct crypto_shash *tfm;
	struct shash_desc *desc;
	size_t digest_size, desc_size;
	void *digest;
	int ret;

	kenter(",%u", ctx->digest_algo);


	tfm = crypto_alloc_shash(hash_algo_name[ctx->digest_algo], 0, 0);
	if (IS_ERR(tfm))
		return (PTR_ERR(tfm) == -ENOENT) ? -ENOPKG : PTR_ERR(tfm);

	desc_size = crypto_shash_descsize(tfm) + sizeof(*desc);
	digest_size = crypto_shash_digestsize(tfm);

	if (digest_size != ctx->digest_len) {
		pr_debug("Digest size mismatch (%zx != %x)\n",
			 digest_size, ctx->digest_len);
		ret = -EBADMSG;
		goto error_no_desc;
	}
	pr_debug("Digest: desc=%zu size=%zu\n", desc_size, digest_size);

	ret = -ENOMEM;
	desc = kzalloc(desc_size + digest_size, GFP_KERNEL);
	if (!desc)
		goto error_no_desc;

	desc->tfm   = tfm;
	desc->flags = CRYPTO_TFM_REQ_MAY_SLEEP;
	ret = crypto_shash_init(desc);
	if (ret < 0)
		goto error;

	ret = pefile_digest_pe_contents(pebuf, pelen, ctx, desc);
	if (ret < 0)
		goto error;

	digest = (void *)desc + desc_size;
	ret = crypto_shash_final(desc, digest);
	if (ret < 0)
		goto error;

	pr_debug("Digest calc = [%*ph]\n", ctx->digest_len, digest);


	if (memcmp(digest, ctx->digest, ctx->digest_len) != 0) {
		pr_debug("Digest mismatch\n");
		ret = -EKEYREJECTED;
	} else {
		pr_debug("The digests match!\n");
	}

error:
	kfree(desc);
error_no_desc:
	crypto_free_shash(tfm);
	kleave(" = %d", ret);
	return ret;
}
