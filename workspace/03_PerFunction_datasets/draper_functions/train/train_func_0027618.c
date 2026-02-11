_pos(Request& r, MethodParams& params) {
	Value& substr=params.as_no_junction(0, "substr must not be code");

	const String& string=GET_SELF(r, VString).string();
	ssize_t offset=0;
	if(params.count()>1){
		offset=params.as_int(1, "n must be int", r);
		if(offset<0)
			throw Exception(PARSER_RUNTIME,
				0,
				"n(%d) must be >=0", offset);
	}

	r.write_no_lang(*new VInt((int)string.pos(r.charsets.source(), substr.as_string(), (size_t)offset)));
}
