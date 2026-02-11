decode_json_array(json_string *injson) {
	if(injson == NULL || injson->offset == NULL) return NULL;

	json_value *out = apr_palloc(injson->mpool,sizeof(json_value));
	out->value.array = apr_array_make(injson->mpool,strlen(injson->offset)/2,sizeof(json_value *));
	out->type = JSON_ARRAY;

	injson->offset++;
	while(isspace(*injson->offset)) injson->offset++;
	if(*(injson->offset) == ']') {
		injson->offset++;
		return out;
	}

	json_value *element = decode_json_value(injson);
	if(element==NULL) return NULL;
	*((json_value**)(apr_array_push(out->value.array))) = element;

	while(*(injson->offset)!='\0' && *(injson->offset)!=']') {
		while(isspace(*injson->offset)) injson->offset++;
		switch(*(injson->offset)) {
			case ']':
					goto array_closure;
			case ',':
					injson->offset++;
					if((element = decode_json_value(injson))==NULL) {
						return NULL;
					}
					*((json_value**)(apr_array_push(out->value.array))) = element;
					break;
			default:
					return NULL;
		}
	}
array_closure:
		if(*(injson->offset) !=']') return NULL;
		injson->offset++;
	return out;
}
