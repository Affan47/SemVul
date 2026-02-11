read_packed(git_rawobj *out, const pack_location *loc)
{
	index_entry e;
	int res;

	assert(out && loc);

	if (pack_openidx(loc->ptr) < 0)
		return GIT_EPACKCORRUPTED;

	res = loc->ptr->idx_get(&e, loc->ptr, loc->n);

	if (!res)
		res = unpack_object(out, loc->ptr, &e);

	pack_decidx(loc->ptr);

	return res;
}
