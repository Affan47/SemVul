maybe_change_string_literal_to_double_literal(ArrayOperation& literal_array) {
	assert(literal_array[0].code==OP::OP_VALUE);
	VString& vstring=*static_cast<VString*>(literal_array[2].value);
	if(isdigit(vstring.string().first_char()))
		literal_array.put(2, &vstring.as_expr_result());
}
