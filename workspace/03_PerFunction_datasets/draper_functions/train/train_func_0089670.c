print_rule_section(const poldiff_t * diff, const poldiff_component_record_t * rec, const apol_vector_t * v,
			       poldiff_form_e form)
{
	int i;
	char *str = NULL;
	const void *item1;

	for (i = 0; i < apol_vector_get_size(v); i++) {
		item1 = apol_vector_get_element(v, i);
		if (poldiff_component_record_get_form_fn(rec) (item1) == form) {
			if ((str = poldiff_component_record_get_to_string_fn(rec) (diff, item1)) == NULL) {
				return;
			}
			print_diff_string(str, 1);
			printf("\n");
			free(str);
			str = NULL;
		}
	}
}
