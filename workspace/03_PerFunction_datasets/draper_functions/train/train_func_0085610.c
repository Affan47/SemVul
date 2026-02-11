auparse_find_field_next(auparse_state_t *au)
{
	if (au->find_field == NULL) {
		errno = EINVAL;
		return NULL;
	}
	if (au->le.e.sec) {
		int moved = 0;

		rnode *r = aup_list_get_cur(&au->le);
		while (r) {
			if (!moved) {
				nvlist_next(&r->nv);
				moved=1;
			}
			if (nvlist_find_name(&r->nv, au->find_field))
				return nvlist_get_cur_val(&r->nv);
			r = aup_list_next(&au->le);
			if (r)
				aup_list_first_field(&au->le);
		}
	}
	return NULL;
}
