_html(Request& r, MethodParams& params) {

	String tag;
	tag << "<img";

	const HashStringValue& fields=GET_SELF(r, VImage).fields();
	HashStringValue* attribs=0;

	if(params.count()) {

		Value& vattribs=r.process_to_value(params[0], false);
		if(!vattribs.is_string())
			if((attribs=vattribs.get_hash())) {
				Attrib_info info={&tag, 0};
				attribs->for_each<Attrib_info*>(append_attrib_pair, &info);
			} else
				throw Exception(PARSER_RUNTIME,
					0,
					"attributes must be hash");
	}

	{
		Attrib_info info={&tag, attribs};
		fields.for_each<Attrib_info*>(append_attrib_pair, &info);
	}
	tag << " />";
	r.write_pass_lang(tag);
}
