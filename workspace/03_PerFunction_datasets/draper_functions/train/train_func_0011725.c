pkcs7_sig_note_digest_algo(void *context, size_t hdrlen,
			       unsigned char tag,
			       const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	switch (ctx->last_oid) {
	case OID_md4:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_MD4;
		break;
	case OID_md5:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_MD5;
		break;
	case OID_sha1:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_SHA1;
		break;
	case OID_sha256:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_SHA256;
		break;
	case OID_sha384:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_SHA384;
		break;
	case OID_sha512:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_SHA512;
		break;
	case OID_sha224:
		ctx->sinfo->sig.pkey_hash_algo = HASH_ALGO_SHA224;
	default:
		printk("Unsupported digest algo: %u\n", ctx->last_oid);
		return -ENOPKG;
	}
	return 0;
}
