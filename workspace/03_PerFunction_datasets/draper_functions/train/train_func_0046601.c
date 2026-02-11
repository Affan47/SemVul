bcf_call_del_rghash(void *_hash)
{
	khint_t k;
	khash_t(rg) *hash = (khash_t(rg)*)_hash;
	if (hash == 0) return;
	for (k = kh_begin(hash); k < kh_end(hash); ++k)
		if (kh_exist(hash, k))
			free((char*)kh_key(hash, k));
	kh_destroy(rg, hash);
}
