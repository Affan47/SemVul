file_delete(const String& file_spec, bool fail_on_problem, bool keep_empty_dirs) {
	const char* fname=file_spec.taint_cstr(String::L_FILE_SPEC);
	if(unlink(fname)!=0)
		if(fail_on_problem)
			throw Exception(errno==EACCES?"file.access":errno==ENOENT?"file.missing":0,
				&file_spec,
				"unlink failed: %s (%d), actual filename '%s'",
					strerror(errno), errno, fname);
		else
			return false;

	if(!keep_empty_dirs)
		rmdir(file_spec, 1);

	return true;
}
