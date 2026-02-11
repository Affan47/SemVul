write(Value& avalue) {
	if(fvalue) {

		throw Exception(PARSER_RUNTIME,
			fvalue->get_class()?&fvalue->get_class()->name():0,
			"%s may not be overwritten with %s, store it to variable instead",
				fvalue->type(),
				avalue.type());
	} else
		fvalue=&avalue;
}
