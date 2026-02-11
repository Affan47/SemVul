free_bzdata(void *valptr, size_t len)
{
	struct bzdata *bz = valptr;

	g_assert(sizeof *bz == len);

	atom_str_free_null(&bz->mime_type);
	atom_str_free_null(&bz->mime_desc);
	HFREE_NULL(bz->ticket);
}
