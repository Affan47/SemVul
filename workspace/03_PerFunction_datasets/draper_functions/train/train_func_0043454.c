ima_get_hash_algo(struct evm_ima_xattr_data *xattr_value, int xattr_len,
		       struct ima_digest_data *hash)
{
	struct signature_v2_hdr *sig;

	if (!xattr_value || xattr_len < 2)
		return;

	switch (xattr_value->type) {
	case EVM_IMA_XATTR_DIGSIG:
		sig = (typeof(sig))xattr_value;
		if (sig->version != 2 || xattr_len <= sizeof(*sig))
			return;
		hash->algo = sig->hash_algo;
		break;
	case IMA_XATTR_DIGEST_NG:
		hash->algo = xattr_value->digest[0];
		if (hash->algo >= HASH_ALGO__LAST)
			hash->algo = ima_hash_algo;
		break;
	case IMA_XATTR_DIGEST:

		if (xattr_len == 21) {
			unsigned int zero = 0;
			if (!memcmp(&xattr_value->digest[16], &zero, 4))
				hash->algo = HASH_ALGO_MD5;
			else
				hash->algo = HASH_ALGO_SHA1;
		} else if (xattr_len == 17)
			hash->algo = HASH_ALGO_MD5;
		break;
	}
}
