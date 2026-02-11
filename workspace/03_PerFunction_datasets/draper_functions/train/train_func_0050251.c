get_untaint_lang(const String& lang_name){
	String::Language lang=untaint_lang_name2enum.get(lang_name);
	if(!lang)
		throw Exception(PARSER_RUNTIME,	&lang_name, "invalid taint language");
	return lang;
}
