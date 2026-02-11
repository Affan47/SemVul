primitive_modify_code_heap(void)
{
	F_ARRAY *alist = untag_array(dpop());

	CELL count = untag_fixnum_fast(alist->capacity);
	if(count == 0)
		return;

	CELL i;
	for(i = 0; i < count; i++)
	{
		F_ARRAY *pair = untag_array(array_nth(alist,i));

		F_WORD *word = untag_word(array_nth(pair,0));

		CELL data = array_nth(pair,1);

		if(type_of(data) == QUOTATION_TYPE)
		{
			REGISTER_UNTAGGED(alist);
			REGISTER_UNTAGGED(word);
			jit_compile_word(word,data,false);
			UNREGISTER_UNTAGGED(word);
			UNREGISTER_UNTAGGED(alist);
		}
		else if(type_of(data) == ARRAY_TYPE)
		{
			F_ARRAY *compiled_code = untag_array(data);

			F_ARRAY *literals = untag_array(array_nth(compiled_code,0));
			CELL relocation = array_nth(compiled_code,1);
			F_ARRAY *labels = untag_array(array_nth(compiled_code,2));
			F_ARRAY *code = untag_array(array_nth(compiled_code,3));

			REGISTER_UNTAGGED(alist);
			REGISTER_UNTAGGED(word);

			F_CODE_BLOCK *compiled = add_code_block(
				WORD_TYPE,
				code,
				labels,
				relocation,
				tag_object(literals));

			UNREGISTER_UNTAGGED(word);
			UNREGISTER_UNTAGGED(alist);

			set_word_code(word,compiled);
		}
		else
			critical_error("Expected a quotation or an array",data);

		REGISTER_UNTAGGED(alist);
		update_word_xt(word);
		UNREGISTER_UNTAGGED(alist);
	}

	update_code_heap_words();
}
