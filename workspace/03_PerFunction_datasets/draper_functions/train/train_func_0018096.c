field_cache_cmp (void *mp1, void *mp2) {
	struct field_list	*fl1;
	struct field_list	*fl2;
	int			ret;

	fl1 = (struct field_list *)mp1;
	fl2 = (struct field_list *)mp2;
	ret = strcasecmp (fl1->curr_prog, fl2->curr_prog);
	if (ret) {
		return ret;
	}
	return fl1->f->id - fl2->f->id;
}
