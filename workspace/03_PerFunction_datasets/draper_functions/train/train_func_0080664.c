_method_info(Request& r, MethodParams& params) {
	const String& class_name=params.as_string(0, "class_name must be string");
	Value* class_value=r.get_class(class_name);
	if(!class_value)
		throw Exception(PARSER_RUNTIME,
			&class_name,
			"class is undefined");

	VStateless_class* lclass=class_value->get_class();
	if(!lclass)
		throw Exception(PARSER_RUNTIME,
			&class_name,
			"class does not have methods");

	const String& method_name=params.as_string(1, "method_name must be string");
	Method* method=lclass->get_method(method_name);
	if(!method)
		throw Exception(PARSER_RUNTIME,
			&method_name,
			"method not found in class %s",
			class_name.cstr());

	VHash& result=*new VHash;
	HashStringValue* hash=result.get_hash();

	VStateless_class* c=lclass;
	Method* base_method;
	if(c->base() && (base_method=c->base()->get_method(method_name))){
		c=c->base()->get_class();
		while(c->base() && base_method==c->base()->get_method(method_name))
			c=c->base()->get_class();
		hash->put((base_method==method) ? method_inherited : method_overridden, new VString(c->name()));
	}

	Value* call_type=0;
	switch(method->call_type){
		case Method::CT_DYNAMIC:
			call_type=new VString(method_call_type_dynamic);
			break;
		case Method::CT_STATIC:
			call_type=new VString(method_call_type_static);
			break;
	}
	if(call_type)
		hash->put(method_call_type, call_type);

	if(method->native_code){

		hash->put(method_min_params, new VInt(method->min_numbered_params_count));
		hash->put(method_max_params, new VInt(method->max_numbered_params_count));
	} else {

		const String* filespec = r.get_method_filename(method);
		if( filespec )
			hash->put("file", new VString(*filespec));

		hash->put(method_max_params, new VInt(method->params_names ? method->params_names->count() : 0));

		if(method->params_names)
			for(size_t i=0; i<method->params_names->count(); i++)
				hash->put(String::Body::Format(i), new VString(*method->params_names->get(i)));

		if(method->extra_params)
			hash->put(method_extra_param, new VString(*method->extra_params));
	}

	r.write_no_lang(result);
}
