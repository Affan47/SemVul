realpath(const char *file_name,char *resolved_name) {
	char *result;

	if (!libc_handle)
		initialize();


	if( !(__instw.gstatus & INSTW_INITIALIZED) ||
	    !(__instw.gstatus & INSTW_OKWRAP) ) {
		result=true_realpath(file_name,resolved_name);
		return result;
	}

	result=true_realpath(file_name,resolved_name);

	return result;
}
