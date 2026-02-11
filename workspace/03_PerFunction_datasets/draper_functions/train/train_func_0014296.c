Validate(FreeImageIO *io, fi_handle handle) {
	char buffer[256];


	int count = io->read_proc(buffer, 1, 256, handle);
	if(count <= 9) return FALSE;
	for(int i = 0; i < (count - 9); i++) {
		if(strncmp(&buffer[i], "/* XPM */", 9) == 0)
			return TRUE;
	}
	return FALSE;
}
