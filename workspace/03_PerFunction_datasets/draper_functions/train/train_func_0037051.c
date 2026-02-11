auparse_next_field(auparse_state_t *au)
{
	rnode *r = aup_list_get_cur(&au->le);
	if (r) {
		if (nvlist_next(&r->nv))
			return 1;
		else
			return 0;
	}
	return 0;
}
