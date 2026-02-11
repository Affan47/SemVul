json_print(json_object *j, int depth) {
	if (j == NULL) {

		printf("NULL");
	} else if (j->type == JSON_HASH) {
		printf("{\n");
		indent(depth + 1);

		int i;
		for (i = 0; i < j->length; i++) {
			json_print(j->keys[i], depth + 1);
			printf(" : ");
			json_print(j->values[i], depth + 1);
			if (i + 1 < j->length) {
				printf(",\n");
				indent(depth + 1);
			}
		}
		printf("\n");
		indent(depth);
		printf("}");
	} else if (j->type == JSON_ARRAY) {
		printf("[\n");
		indent(depth + 1);

		int i;
		for (i = 0; i < j->length; i++) {
			json_print(j->array[i], depth + 1);
			if (i + 1 < j->length) {
				printf(",\n");
				indent(depth + 1);
			}
		}
		printf("\n");
		indent(depth);
		printf("]");
	} else {
		json_print_one(j, &depth);
	}
}
