file_move(const String& old_spec, const String& new_spec, bool keep_empty_dirs) {
	const char* old_spec_cstr=old_spec.taint_cstr(String::L_FILE_SPEC);
	const char* new_spec_cstr=new_spec.taint_cstr(String::L_FILE_SPEC);

	create_dir_for_file(new_spec);

	if(rename(old_spec_cstr, new_spec_cstr)!=0)
		throw Exception(errno==EACCES?"file.access":errno==ENOENT?"file.missing":0,
			&old_spec,
			"rename failed: %s (%d), actual filename '%s' to '%s'",
				strerror(errno), errno, old_spec_cstr, new_spec_cstr);

	if(!keep_empty_dirs)
		rmdir(old_spec, 1);
}
