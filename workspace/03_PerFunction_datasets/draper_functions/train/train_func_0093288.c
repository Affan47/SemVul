compile_all_words()
{
	data_root<array> words(find_all_words(),this);

	cell length = array_capacity(words.untagged());
	for(cell i = 0; i < length; i++)
	{
		data_root<word> word(array_nth(words.untagged(),i),this);

		if(!word->entry_point || !word->code()->optimized_p())
			jit_compile_word(word.value(),word->def,false);
	}
}
