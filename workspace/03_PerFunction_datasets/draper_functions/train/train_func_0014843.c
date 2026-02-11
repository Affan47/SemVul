isl_hash_id(uint32_t hash, __isl_keep isl_id *id)
{
	if (id)
		isl_hash_hash(hash, id->hash);

	return hash;
}
