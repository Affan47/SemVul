build_v3_fingerprint(chunk_t *encoding, va_list args)
{
	hasher_t *hasher;
	chunk_t n, e;

	if (cred_encoding_args(args, CRED_PART_RSA_MODULUS, &n,
						   CRED_PART_RSA_PUB_EXP, &e, CRED_PART_END))
	{
		hasher = lib->crypto->create_hasher(lib->crypto, HASH_MD5);
		if (!hasher)
		{
			DBG1(DBG_LIB, "MD5 hash algorithm not supported, PGP"
				 " fingerprinting failed");
			return FALSE;
		}

		while (n.len > 0 && n.ptr[0] == 0x00)
		{
			n = chunk_skip(n, 1);
		}
		while (e.len > 0 && e.ptr[0] == 0x00)
		{
			e = chunk_skip(e, 1);
		}
		if (!hasher->allocate_hash(hasher, n, NULL) ||
			!hasher->allocate_hash(hasher, e, encoding))
		{
			hasher->destroy(hasher);
			return FALSE;
		}
		hasher->destroy(hasher);
		return TRUE;
	}
	return FALSE;
}
