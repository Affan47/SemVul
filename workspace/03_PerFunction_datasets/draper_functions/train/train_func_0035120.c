pkcs7_digest(struct pkcs7_message *pkcs7,
			struct pkcs7_signed_info *sinfo)
{
	struct crypto_shash *tfm;
	struct shash_desc *desc;
	size_t digest_size, desc_size;
	void *digest;
	int ret;

	kenter(",%u,%u", sinfo->index, sinfo->sig.pkey_hash_algo);

	if (sinfo->sig.pkey_hash_algo >= PKEY_HASH__LAST ||
	    !hash_algo_name[sinfo->sig.pkey_hash_algo])
		return -ENOPKG;


	tfm = crypto_alloc_shash(hash_algo_name[sinfo->sig.pkey_hash_algo],
				 0, 0);
	if (IS_ERR(tfm))
		return (PTR_ERR(tfm) == -ENOENT) ? -ENOPKG : PTR_ERR(tfm);

	desc_size = crypto_shash_descsize(tfm) + sizeof(*desc);
	sinfo->sig.digest_size = digest_size = crypto_shash_digestsize(tfm);

	ret = -ENOMEM;
	digest = kzalloc(ALIGN(digest_size, __alignof__(*desc)) + desc_size,
			 GFP_KERNEL);
	if (!digest)
		goto error_no_desc;

	desc = PTR_ALIGN(digest + digest_size, __alignof__(*desc));
	desc->tfm   = tfm;
	desc->flags = CRYPTO_TFM_REQ_MAY_SLEEP;


	ret = crypto_shash_init(desc);
	if (ret < 0)
		goto error;
	ret = crypto_shash_finup(desc, pkcs7->data, pkcs7->data_len, digest);
	if (ret < 0)
		goto error;
	pr_devel("MsgDigest = [%*ph]\n", 8, digest);


	if (sinfo->authattrs) {
		u8 tag;

		if (!sinfo->msgdigest) {
			pr_warn("Sig %u: No messageDigest\n", sinfo->index);
			ret = -EKEYREJECTED;
			goto error;
		}

		if (sinfo->msgdigest_len != sinfo->sig.digest_size) {
			pr_debug("Sig %u: Invalid digest size (%u)\n",
				 sinfo->index, sinfo->msgdigest_len);
			ret = -EBADMSG;
			goto error;
		}

		if (memcmp(digest, sinfo->msgdigest, sinfo->msgdigest_len) != 0) {
			pr_debug("Sig %u: Message digest doesn't match\n",
				 sinfo->index);
			ret = -EKEYREJECTED;
			goto error;
		}


		memset(digest, 0, sinfo->sig.digest_size);

		ret = crypto_shash_init(desc);
		if (ret < 0)
			goto error;
		tag = ASN1_CONS_BIT | ASN1_SET;
		ret = crypto_shash_update(desc, &tag, 1);
		if (ret < 0)
			goto error;
		ret = crypto_shash_finup(desc, sinfo->authattrs,
					 sinfo->authattrs_len, digest);
		if (ret < 0)
			goto error;
		pr_devel("AADigest = [%*ph]\n", 8, digest);
	}

	sinfo->sig.digest = digest;
	digest = NULL;

error:
	kfree(digest);
error_no_desc:
	crypto_free_shash(tfm);
	kleave(" = %d", ret);
	return ret;
}
