_dirname(Request& r, MethodParams& params) {
	const String& file_spec=params.as_string(0, FILE_NAME_MUST_BE_STRING);


	if(file_spec.is_empty()) {
		r.write_assign_lang(String("."));
		return;
	}

	size_t p;
	size_t slash;
	if((p=file_spec.rskipchars("/\\"))==STRING_NOT_FOUND)
		r.write_assign_lang(String("/"));
	else {
		if((slash=file_spec.strrpbrk("/\\", 0, p))!=STRING_NOT_FOUND) {
			if((p=file_spec.rskipchars("/\\", 0, slash))==STRING_NOT_FOUND)
				p=slash;
			r.write_assign_lang(file_spec.mid(0, p+1));
			return;
		}
		r.write_assign_lang(String("."));
	}
}
