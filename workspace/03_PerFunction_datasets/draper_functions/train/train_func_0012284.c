synctex_scanner_new_with_output_file(const char * output, const char * build_directory, int parse) {
	gzFile file = NULL;
	char * synctex = NULL;
	synctex_scanner_t scanner = NULL;
	synctex_io_mode_t io_mode = 0;

	if (sizeof(int)>sizeof(void*)) {
		_synctex_error("INTERNAL INCONSISTENCY: int's are unexpectedly bigger than pointers, bailing out.");
		return NULL;
	}

	if (SYNCTEX_BUFFER_SIZE >= UINT_MAX) {
		_synctex_error("SyncTeX BUG: Internal inconsistency, bad SYNCTEX_BUFFER_SIZE (1)");
		return NULL;
	}

	if (SYNCTEX_BUFFER_SIZE < SYNCTEX_BUFFER_MIN_SIZE) {
		_synctex_error("SyncTeX BUG: Internal inconsistency, bad SYNCTEX_BUFFER_SIZE (2)");
		return NULL;
	}

	if (_synctex_open(output,build_directory,&synctex,&file,synctex_ADD_QUOTES,&io_mode) || !file) {
		if (_synctex_open(output,build_directory,&synctex,&file,synctex_DONT_ADD_QUOTES,&io_mode) || !file) {
			return NULL;
		}
	}
	scanner = (synctex_scanner_t)_synctex_malloc(sizeof(_synctex_scanner_t));
	if (NULL == scanner) {
		_synctex_error("SyncTeX: malloc problem");
		free(synctex);
		gzclose(file);
		return NULL;
	}

	if (NULL == (scanner->output = (char *)malloc(strlen(output)+1))){
		_synctex_error("!  synctex_scanner_new_with_output_file: Memory problem (2), scanner's output is not reliable.");
	} else if (scanner->output != strcpy(scanner->output,output)) {
		_synctex_error("!  synctex_scanner_new_with_output_file: Copy problem, scanner's output is not reliable.");
	}
	scanner->synctex = synctex;
	SYNCTEX_FILE = file;
	return parse? synctex_scanner_parse(scanner):scanner;
}
