Validate(FreeImageIO *io, fi_handle handle) {
	DDSHEADER header;
	memset(&header, 0, sizeof(header));
	io->read_proc(&header, 1, sizeof(header), handle);
#ifdef FREEIMAGE_BIGENDIAN
	SwapHeader(&header);
#endif
	if (header.dwMagic != MAKEFOURCC ('D','D','S',' '))
		return FALSE;
	if (header.surfaceDesc.dwSize != sizeof (header.surfaceDesc) ||
		header.surfaceDesc.ddpfPixelFormat.dwSize != sizeof (header.surfaceDesc.ddpfPixelFormat))
		return FALSE;
	return TRUE;
}
