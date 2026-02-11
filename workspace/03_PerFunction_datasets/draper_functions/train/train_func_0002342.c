_int(Request& r, MethodParams&) {
	VInt& vint=GET_SELF(r, VInt);
	r.write_no_lang(*new VInt(vint.get_int()));
}
