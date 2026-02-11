ast_data_search_match(const struct ast_data_search *search, struct ast_data *data)
{
	struct ao2_iterator i, ii;
	struct ast_data_search *s, *s_child;
	struct ast_data *d_child;
	int notmatch = 1;

	if (!search) {
		return 1;
	}

	s_child = data_search_find(search->children, data->name);
	if (!s_child) {

		ao2_ref(s_child, -1);
		return 1;
	}

	i = ao2_iterator_init(s_child->children, 0);
	while ((s = ao2_iterator_next(&i))) {
		if (!ao2_container_count(s->children)) {

			d_child = data_result_find_child(data, s->name);
			if (!d_child) {
				ao2_ref(s, -1);
				notmatch = 1;
				continue;
			}

			switch (d_child->type) {
			case AST_DATA_PASSWORD:
			case AST_DATA_STRING:
				notmatch = data_search_cmp_string(s_child, d_child->name,
					d_child->payload.str);
				break;
			case AST_DATA_CHARACTER:
				notmatch = data_search_cmp_char(s_child, d_child->name,
					d_child->payload.character);
				break;
			case AST_DATA_INTEGER:
				notmatch = data_search_cmp_int(s_child, d_child->name,
					d_child->payload.sint);
				break;
			case AST_DATA_BOOLEAN:
				notmatch = data_search_cmp_bool(s_child, d_child->name,
					d_child->payload.boolean);
				break;
			case AST_DATA_UNSIGNED_INTEGER:
				notmatch = data_search_cmp_uint(s_child, d_child->name,
					d_child->payload.uint);
				break;
			case AST_DATA_TIMESTAMP:
			case AST_DATA_SECONDS:
			case AST_DATA_MILLISECONDS:
			case AST_DATA_DOUBLE:
				notmatch = data_search_cmp_uint(s_child, d_child->name,
					d_child->payload.dbl);
				break;
			case AST_DATA_IPADDR:
				notmatch = data_search_cmp_ipaddr(s_child, d_child->name,
					d_child->payload.ipaddr);
				break;
			case AST_DATA_POINTER:
				notmatch = data_search_cmp_ptr(s_child, d_child->name,
					d_child->payload.ptr);
				break;
			case AST_DATA_CONTAINER:
				break;
			}
			ao2_ref(d_child, -1);
		} else {
			ii = ao2_iterator_init(data->children, 0);
			while ((d_child = ao2_iterator_next(&ii))) {
				if (strcmp(d_child->name, s->name)) {
					ao2_ref(d_child, -1);
					continue;
				}
				if (!(notmatch = !ast_data_search_match(s_child, d_child))) {

					ao2_ref(d_child, -1);
					break;
				}
				ao2_ref(d_child, -1);
			}
			ao2_iterator_destroy(&ii);
		}
		ao2_ref(s, -1);
		if (notmatch) {

			break;
		}
	}
	ao2_iterator_destroy(&i);

	ao2_ref(s_child, -1);

	return !notmatch;
}
