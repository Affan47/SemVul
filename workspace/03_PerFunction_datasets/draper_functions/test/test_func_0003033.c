anwcs_open(const char* filename, int ext) {
	char* errmsg;
	anwcs_t* anwcs = NULL;
	errors_start_logging_to_string();


	anwcs = anwcs_open_sip(filename, ext);
	if (anwcs) {
		errors_pop_state();
		return anwcs;
	} else {
		errmsg = errors_stop_logging_to_string("\n  ");
		logverb("Failed to open file %s, ext %i as SIP:\n%s\n", filename, ext, errmsg);
		free(errmsg);
	}


	anwcs = anwcs_open_wcslib(filename, ext);
	if (anwcs) {
		errors_pop_state();
		return anwcs;
	} else {
		errmsg = errors_stop_logging_to_string(": ");
		logverb("Failed to open file %s, ext %i using WCSLIB: %s", filename, ext, errmsg);
		free(errmsg);
	}


	anwcs = anwcs_open_wcstools(filename, ext);
	if (anwcs) {
		errors_pop_state();
		return anwcs;
	} else {
		errmsg = errors_stop_logging_to_string(": ");
		logverb("Failed to open file %s, ext %i using WCStools: %s", filename, ext, errmsg);
		free(errmsg);
	}

	return NULL;
}
