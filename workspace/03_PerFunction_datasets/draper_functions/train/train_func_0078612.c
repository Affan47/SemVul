lt_error_is_set(lt_error_t      *error,
		lt_error_type_t  type)
{
	if (type == LT_ERR_ANY) {
		return error && error->data;
	} else {
		if (error && error->data) {
			lt_list_t *l;

			for (l = error->data; l != NULL; l = lt_list_next(l)) {
				lt_error_data_t *d = lt_list_value(l);

				if (d->type == type)
					return TRUE;
			}
		}
	}

	return FALSE;
}
