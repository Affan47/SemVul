regex_options(const String* options, int* result){
	struct Regex_option {
		const char* key;
		const char* keyAlt;
		int clear;
		int set;
		int *result;
	} regex_option[]={
		{"i", "I", 0, PCRE_CASELESS, result},
		{"s", "S", 0, PCRE_DOTALL, result},
		{"m", "M", PCRE_DOTALL, PCRE_MULTILINE, result},
		{"x", 0, 0, PCRE_EXTENDED, result},
		{"U", 0, 0, PCRE_UNGREEDY, result},
		{"g", "G", 0, MF_GLOBAL_SEARCH, result+1},
		{"'", 0, 0, MF_NEED_PRE_POST_MATCH, result+1},
		{"n", 0, 0, MF_JUST_COUNT_MATCHES, result+1},
		{0, 0, 0, 0, 0}
	};
	result[0]=PCRE_EXTRA
			| PCRE_DOTALL
			| PCRE_DOLLAR_ENDONLY ;
	result[1]=0;

	if(options && !options->is_empty()){
		size_t valid_options=0;
		for(Regex_option *o=regex_option; o->key; o++)
			if(
				options->pos(o->key)!=STRING_NOT_FOUND
				|| (o->keyAlt && options->pos(o->keyAlt)!=STRING_NOT_FOUND)
			){
				*o->result &= ~o->clear;
				*o->result |= o->set;
				valid_options++;
			}
		if(options->length()!=valid_options)
			throw Exception(PARSER_RUNTIME, 0, CALLED_WITH_INVALID_OPTION);
	}
}
