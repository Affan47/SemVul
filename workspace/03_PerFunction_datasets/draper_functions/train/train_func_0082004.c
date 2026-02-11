bson_string_output(bson_t *b, size_t *sz) {

	char *s = NULL, *s_obj = NULL;
	size_t sz_obj;
	*sz = 0;
	int64_t i64;
	int32_t i32;

	switch(b->type) {
		case BSON_ARRAY:
		case BSON_OBJECT:
			s_obj = bson_string_output_object(b, &sz_obj);
			*sz = sizeof(i32) + sz_obj + 1;
			s = malloc(*sz);
			i32 = *sz;
			memcpy(s, &i32, sizeof(i32));
			memcpy(s + sizeof(i32), s_obj, sz_obj);
			s[*sz-1] = 0;
			free(s_obj);
			break;

		case BSON_TRUE:
			*sz = 1;
			s = malloc(*sz);
			*s = 1;
			break;

		case BSON_FALSE:
			*sz = 1;
			s = malloc(*sz);
			*s = 0;
			break;

		case BSON_INT:
			*sz = 8;
			i64 = b->data.i;
			s = malloc(*sz);
			memcpy(s, &i64, sizeof(i64));
			break;

		case BSON_BIN:
			i32 = b->data.bin.sz;
			*sz = sizeof(i32) + 1 + i32;
			s = malloc(*sz);
			memcpy(s, &i32, sizeof(i32));
			s[sizeof(i32)] = 0;
			memcpy(s + sizeof(i32) + 1, b->data.bin.s, b->data.bin.sz);
			break;

		case BSON_STRING:
			i32 = b->data.bin.sz + 1;
			*sz = sizeof(i32) + i32;
			s = malloc(*sz);
			memcpy(s, &i32, sizeof(i32));
			memcpy(s + sizeof(i32), b->data.bin.s, b->data.bin.sz);
			s[*sz - 1] = 0;
			break;

		case BSON_NULL:
			*sz = 0;
			return NULL;
			break;
	}

	return s;

}
