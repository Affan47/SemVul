mdb_leaf_size(MDB_env *env, MDB_val *key, MDB_val *data)
{
	size_t		 sz;

	sz = LEAFSIZE(key, data);
	if (sz >= env->me_psize / MDB_MINKEYS) {

		sz -= data->mv_size - sizeof(pgno_t);
	}
	sz += sz & 1;

	return sz + sizeof(indx_t);
}
