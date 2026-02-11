cstr_to_string_body_block_untaint(char alang, size_t fragment_length, Cstr_to_string_body_block_info* info){
	const String::Language lang=(String::Language)(unsigned char)alang;

	if(info->lang&String::L_OPTIMIZE_BIT)
		return cstr_to_string_body_block(
			lang==String::L_TAINTED?
				info->lang
				:lang==String::L_CLEAN?
					(String::Language)(String::L_CLEAN|String::L_OPTIMIZE_BIT)
					:lang,
			fragment_length, info);
	else
		return cstr_to_string_body_block(lang==String::L_TAINTED ? info->lang:lang, fragment_length, info);
}
