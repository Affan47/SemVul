_k_key_derive_simple1024
(	const char*	pass,
	void*		salt,
	size_t		salt_bytes,
	uint64_t	iter)
{
	k_hash_t* h = k_hash_init(HASHSUM_SKEIN_1024, 1024);
	if (!h)
		return 0;
	size_t sp = strlen(pass);
	size_t digestbytes = k_hash_digest_bytes(h);

	void* inp = k_malloc(sp+digestbytes);
	if (!inp) {
		k_hash_finish(h);
		return 0;
	}
	void* outp = k_malloc(digestbytes);
	if (!outp) {
		k_free(inp);
		k_hash_finish(h);
		return 0;
	}

	memcpy(inp, pass, sp);
	memcpy(inp+sp, salt, salt_bytes);

	k_hash_update(h, inp, sp+digestbytes);
	k_hash_final(h, outp);
	k_free(inp);

	for (uint64_t i = 0; i < iter; ++i) {
		k_hash_reset(h);
		k_hash_update(h, outp, digestbytes);
		k_hash_final(h, outp);
	}
	k_hash_finish(h);

	return outp;
}
