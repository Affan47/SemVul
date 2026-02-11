Validate(FreeImageIO *io, fi_handle handle) {
	char magic[8];
	if(readLine(magic, 7, io, handle)) {
		if(strcmp(magic, "#define") == 0)
			return TRUE;
	}
	return FALSE;
}
