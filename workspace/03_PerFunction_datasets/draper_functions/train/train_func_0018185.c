deserialize_lifedata(bstr_t *bs, void *valptr, size_t len)
{
	struct lifedata *ld = valptr;

	g_assert(sizeof *ld == len);

	bstr_read_u8(bs, &ld->version);
	bstr_read_time(bs, &ld->first_seen);
	bstr_read_time(bs, &ld->last_seen);
}
