decode_json_boolean(json_string *injson){
	json_value *out = NULL;
	if(injson->end - injson->offset > 3  && strncmp("true",injson->offset,4) == 0) {
		out = apr_palloc(injson->mpool,sizeof(json_value));
		out->value.boolean = 1;
		out->type = JSON_BOOLEAN;
		injson->offset +=4;
	} else if (injson->end - injson->offset > 4 && strncmp("false",injson->offset,5)==0){
		out = apr_palloc(injson->mpool,sizeof(json_value));
		out->value.boolean = 0;
		out->type = JSON_BOOLEAN;
		injson->offset +=5;
	}
	return out;
}
