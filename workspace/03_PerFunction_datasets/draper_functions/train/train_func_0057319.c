_synctex_scan_named(synctex_scanner_t scanner,const char * name,void * value_ref,synctex_decoder_t decoder) {
	synctex_status_t status = 0;
	if (NULL == scanner || NULL == name || NULL == value_ref || NULL == decoder) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
not_found:
	status = _synctex_match_string(scanner,name);
	if (status<SYNCTEX_STATUS_NOT_OK) {
		return status;
	} else if (status == SYNCTEX_STATUS_NOT_OK) {
		status = _synctex_next_line(scanner);
		if (status<SYNCTEX_STATUS_OK) {
			return status;
		}
		goto not_found;
	}

	return (*decoder)(scanner,value_ref);
}
