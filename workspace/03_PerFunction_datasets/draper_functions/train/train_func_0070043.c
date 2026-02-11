auparse_get_num_fields(auparse_state_t *au)
{
	rnode *r = aup_list_get_cur(&au->le);
	if (r)
		return nvlist_get_cnt(&r->nv);
	else
		return 0;
}
