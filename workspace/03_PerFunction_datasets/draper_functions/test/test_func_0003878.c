_handle_array(s_p_values_t *v,
			 const char *value, const char *line, char **leftover)
{
	void *new_ptr;
	void **data;

	if (v->handler != NULL) {

		int rc;
		rc = v->handler(&new_ptr, v->type, v->key, value,
				line, leftover);
		if (rc != 1)
			return rc == 0 ? 0 : -1;
	} else {
		new_ptr = xstrdup(value);
	}
	v->data_count += 1;
	v->data = xrealloc(v->data, (v->data_count)*sizeof(void *));
	data = &((void**)v->data)[v->data_count-1];
	*data = new_ptr;

	return 1;
}
