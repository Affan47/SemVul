config_insert_values_global(server *srv, array *ca, const config_values_t cv[]) {
	size_t i;
	data_unset *du;

	for (i = 0; cv[i].key; i++) {
		data_string *touched;

		if (NULL == (du = array_get_element(ca, cv[i].key))) {


			continue;
		}


		touched = data_string_init();

		buffer_copy_string_len(touched->value, CONST_STR_LEN(""));
		buffer_copy_string_buffer(touched->key, du->key);

		array_insert_unique(srv->config_touched, (data_unset *)touched);
	}

	return config_insert_values_internal(srv, ca, cv);
}
