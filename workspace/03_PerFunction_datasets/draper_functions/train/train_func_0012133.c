s_p_hashtbl_merge(s_p_hashtbl_t *to_hashtbl, s_p_hashtbl_t *from_hashtbl)
{
	int i;
	s_p_values_t **val_pptr, *val_ptr, *match_ptr;

	if (!to_hashtbl || !from_hashtbl)
		return;

	for (i = 0; i < CONF_HASH_LEN; i++) {
		val_pptr = &from_hashtbl[i];
		val_ptr = from_hashtbl[i];
		while (val_ptr) {
			if (val_ptr->data_count == 0) {


				val_pptr = &val_ptr->next;
				val_ptr = val_ptr->next;
				continue;
			}
			match_ptr = _conf_hashtbl_lookup(to_hashtbl,
							 val_ptr->key);
			if (match_ptr) {
				if (match_ptr->data_count == 0) {
					_conf_hashtbl_swap_data(val_ptr,
								match_ptr);
				}
				val_pptr = &val_ptr->next;
				val_ptr = val_ptr->next;
			} else {
				*val_pptr = val_ptr->next;
				val_ptr->next = NULL;
				_conf_hashtbl_insert(to_hashtbl, val_ptr);
				val_ptr = *val_pptr;
			}
		}
	}
}
