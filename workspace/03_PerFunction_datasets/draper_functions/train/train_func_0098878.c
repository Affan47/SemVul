itree_get2(struct itree *itree, uint128_t key_hash,
	       uint64_t *log_remno_ptr, int *hpos_ptr)
{
	uint64_t found = ohamt_search(&itree->tree, key_hash);
	if (found) {
		struct tree_item ti = _unpack(found);
		*log_remno_ptr = ti.log_remno;
		*hpos_ptr = ti.hpos;
		return 1;
	}
	return 0;
}
