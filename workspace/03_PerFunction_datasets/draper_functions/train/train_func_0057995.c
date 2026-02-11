gar_alloc_search_obj(struct gar_subfile *sub, struct gar_search_res *from)
{
	struct gar_search_res *s;
	s = calloc(1, sizeof(*s));
	if (!s)
		return s;
	if (from)
		*s = *from;
	s->sub = sub;
	s->fileid = sub->id;
	gar_subfile_ref(sub);
	return s;
}
