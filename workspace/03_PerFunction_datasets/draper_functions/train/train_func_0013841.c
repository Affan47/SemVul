_mget(Request& r, MethodParams& params) {
	VMemcached& self=GET_SELF(r, VMemcached);
	Value& param=params.as_no_junction(0, PARAM_MUST_NOT_BE_CODE);

	if(param.is_string()){

		ArrayString keys(params.count());

		for(size_t i=0; i<params.count(); i++) {
			keys+=&params.as_string(i, "key must be string");
		}

		r.write_no_lang(self.mget(keys));
	} else {
		Table* table=param.get_table();
		if(table==0){
			throw Exception("memcached", 0, "key must be string or table");
		}

		ArrayString keys(table->count());

		for(size_t i=0; i<table->count(); i++) {
			keys+=table->get(i)->get(0);
		}

		r.write_no_lang(self.mget(keys));
	}
}
