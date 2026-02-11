rgbe_WriteHeader(FreeImageIO *io, fi_handle handle, unsigned width, unsigned height, rgbeHeaderInfo *info) {
	char buffer[HDR_MAXLINE];

	const char *programtype = "RADIANCE";

	if(info && (info->valid & RGBE_VALID_PROGRAMTYPE)) {
		programtype = info->programtype;
	}

	sprintf(buffer, "#?%s\n", programtype);
	if(io->write_proc(buffer, 1, (unsigned int)strlen(buffer), handle) < 1)
		return rgbe_Error(rgbe_write_error, NULL);
	sprintf(buffer, "%s\n", info->comment);
	if(io->write_proc(buffer, 1, (unsigned int)strlen(buffer), handle) < 1)
		return rgbe_Error(rgbe_write_error, NULL);
	sprintf(buffer, "FORMAT=32-bit_rle_rgbe\n");
	if(io->write_proc(buffer, 1, (unsigned int)strlen(buffer), handle) < 1)
		return rgbe_Error(rgbe_write_error, NULL);
	if(info && (info->valid & RGBE_VALID_GAMMA)) {
		sprintf(buffer, "GAMMA=%g\n", info->gamma);
		if(io->write_proc(buffer, 1, (unsigned int)strlen(buffer), handle) < 1)
			return rgbe_Error(rgbe_write_error, NULL);
	}
	if(info && (info->valid & RGBE_VALID_EXPOSURE)) {
		sprintf(buffer,"EXPOSURE=%g\n", info->exposure);
		if(io->write_proc(buffer, 1, (unsigned int)strlen(buffer), handle) < 1)
			return rgbe_Error(rgbe_write_error, NULL);
	}
	sprintf(buffer, "\n-Y %d +X %d\n", height, width);
	if(io->write_proc(buffer, 1, (unsigned int)strlen(buffer), handle) < 1)
		return rgbe_Error(rgbe_write_error, NULL);

	return TRUE;
}
