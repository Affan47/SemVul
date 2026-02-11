compile_profiling_stub(F_WORD *word)
{
	CELL literals = allot_array_1(tag_object(word));
	REGISTER_ROOT(literals);

	F_ARRAY *quadruple = untag_object(userenv[JIT_PROFILING]);

	CELL code = array_nth(quadruple,0);
	REGISTER_ROOT(code);

	CELL rel_type = allot_cell(to_fixnum(array_nth(quadruple,2))
		| (to_fixnum(array_nth(quadruple,1)) << 8));
	CELL rel_offset = array_nth(quadruple,3) * compiled_code_format();

	CELL relocation = allot_array_2(rel_type,rel_offset);

	UNREGISTER_ROOT(code);
	UNREGISTER_ROOT(literals);

	return add_compiled_block(
		WORD_TYPE,
		untag_object(code),
		NULL,
		untag_object(relocation),
		untag_object(literals));
}
