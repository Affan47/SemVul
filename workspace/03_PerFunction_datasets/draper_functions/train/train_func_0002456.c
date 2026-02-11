FreeImage_Save(FREE_IMAGE_FORMAT fif, FIBITMAP *dib, const char *filename, int flags) {
	FreeImageIO io;
	SetDefaultIO(&io);

	FILE *handle = fopen(filename, "w+b");

	if (handle) {
		BOOL success = FreeImage_SaveToHandle(fif, dib, &io, (fi_handle)handle, flags);

		fclose(handle);

		return success;
	} else {
		FreeImage_OutputMessageProc((int)fif, "FreeImage_Save: failed to open file %s", filename);
	}

	return FALSE;
}
