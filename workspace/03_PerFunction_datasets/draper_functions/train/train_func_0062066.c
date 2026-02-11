encode_json_array(json_value *json) {
	printf("[");
	int i;
	for(i = 0; i < json->value.array->nelts; i++) {
			if(i > 0) printf(" , ");
			json_value *v = *((json_value**)(json->value.array->elts + (json->value.array->elt_size * i)));
			encode_json(v);
	}
	printf("]");
}
