_at(Request& r, MethodParams& params) {
	HashStringValue& hash=GET_SELF(r, VHash).hash_ro();
	size_t count=hash.count();

	int pos=0;

	Value& vwhence=*params.get(0);
	if(vwhence.is_string()){
		const String& swhence=*vwhence.get_string();
		if(swhence == "last")
			pos=count-1;
		else if(swhence != "first")
			throw Exception(PARSER_RUNTIME,
				&swhence,
				"whence must be 'first', 'last' or expression");
	} else {
		pos=r.process_to_value(vwhence).as_int();
		if(pos < 0)
			pos+=count;
	}

	if(count && pos >= 0 && (size_t)pos < count){
		if(pos == 0)
			r.write_assign_lang(*hash.first_value());
		else if((size_t)pos == count-1)
			r.write_assign_lang(*hash.last_value());
		else
			for(HashStringValue::Iterator i(hash); i; i.next(), pos-- )
				if(!pos){
					r.write_assign_lang(*i.value());
					break;
				}
	}

}
