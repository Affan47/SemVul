maybe_make_self(ArrayOperation& opcodes, ArrayOperation& diving_code, size_t divine_count){
	const String* first_name=LA2S(diving_code);

	if(first_name && *first_name==SELF_ELEMENT_NAME){
#ifdef OPTIMIZE_BYTECODE_GET_SELF_ELEMENT
		if(
			divine_count>=8
			&& diving_code[3].code==OP::OP_GET_ELEMENT
			&& diving_code[4].code==OP::OP_VALUE
			&& diving_code[7].code==OP::OP_GET_ELEMENT
		){

			O(opcodes, OP::OP_WITH_SELF__VALUE__GET_ELEMENT);
			P(opcodes, diving_code, 5, 2);
			if(divine_count>8)
				P(opcodes, diving_code, 8);
		} else
#endif
		{


			O(opcodes, OP::OP_WITH_SELF);
			P(opcodes, diving_code, divine_count>=4?4:3);
		}
		return true;
	}
	return false;
}
