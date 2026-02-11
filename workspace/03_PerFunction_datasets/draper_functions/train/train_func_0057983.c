update_word_xt(F_WORD *word)
{
	if(profiling_p)
	{
		if(!word->profiling)
		{
			REGISTER_UNTAGGED(word);
			F_CODE_BLOCK *profiling = compile_profiling_stub(word);
			UNREGISTER_UNTAGGED(word);
			word->profiling = profiling;
		}

		word->xt = (XT)(word->profiling + 1);
	}
	else
		word->xt = (XT)(word->code + 1);
}
