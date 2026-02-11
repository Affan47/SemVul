isl_basic_map_get_hash(__isl_keep isl_basic_map *bmap)
{
	int i;
	uint32_t hash = isl_hash_init();
	unsigned total;

	if (!bmap)
		return 0;
	bmap = isl_basic_map_copy(bmap);
	bmap = isl_basic_map_normalize(bmap);
	if (!bmap)
		return 0;
	total = isl_basic_map_total_dim(bmap);
	isl_hash_byte(hash, bmap->n_eq & 0xFF);
	for (i = 0; i < bmap->n_eq; ++i) {
		uint32_t c_hash;
		c_hash = isl_seq_get_hash(bmap->eq[i], 1 + total);
		isl_hash_hash(hash, c_hash);
	}
	isl_hash_byte(hash, bmap->n_ineq & 0xFF);
	for (i = 0; i < bmap->n_ineq; ++i) {
		uint32_t c_hash;
		c_hash = isl_seq_get_hash(bmap->ineq[i], 1 + total);
		isl_hash_hash(hash, c_hash);
	}
	isl_hash_byte(hash, bmap->n_div & 0xFF);
	for (i = 0; i < bmap->n_div; ++i) {
		uint32_t c_hash;
		if (isl_int_is_zero(bmap->div[i][0]))
			continue;
		isl_hash_byte(hash, i & 0xFF);
		c_hash = isl_seq_get_hash(bmap->div[i], 1 + 1 + total);
		isl_hash_hash(hash, c_hash);
	}
	isl_basic_map_free(bmap);
	return hash;
}
