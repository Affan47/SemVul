_synctex_last_path_component(const char * name) {
	const char * c = name+strlen(name);
	if(c>name) {
		if(!SYNCTEX_IS_PATH_SEPARATOR(*c)) {
			do {
				--c;
				if(SYNCTEX_IS_PATH_SEPARATOR(*c)) {
					return c+1;
				}
			} while(c>name);
		}
		return c;
	}
	return c;
}
