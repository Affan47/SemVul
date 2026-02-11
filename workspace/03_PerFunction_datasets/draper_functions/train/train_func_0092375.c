op_call_write(VMethodFrame& frame){
	VMethodFrame *saved_method_frame=method_frame;
	Value* saved_rcontext=rcontext;

	rcontext=&frame;
	method_frame=&frame;

	Value& self=frame.self();
	const Method& method=frame.method;
	Method::Call_type call_type=self.get_class()==&self ? Method::CT_STATIC : Method::CT_DYNAMIC;

	if(method.call_type==Method::CT_ANY || method.call_type==call_type) {
		if(method.native_code) {
			method.check_actual_numbered_params(self, frame.numbered_params());
			method.native_code(*this, *frame.numbered_params());
		} else
			recoursion_checked_execute(*method.parser_code);
	} else
		throw Exception(PARSER_RUNTIME,
			0,
			"is not allowed to be called %s",
			call_type==Method::CT_STATIC?"statically":"dynamically");

	rcontext=saved_rcontext;
	method_frame=saved_method_frame;
}
