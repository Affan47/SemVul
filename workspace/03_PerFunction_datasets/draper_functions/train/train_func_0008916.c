json_print_array(struct json_array *array)
{
	int i;

	log_info("[\n");
	for (i = 0; i < array->value_cnt; i++) {
		if (i > 0)
			log_info(",\n");
		json_print_level(json_value_level(array->values[i]));
		json_print_value(array->values[i]);
	}
	log_info("\n");
	json_print_level(json_array_level(array));
	log_info("]");
}
