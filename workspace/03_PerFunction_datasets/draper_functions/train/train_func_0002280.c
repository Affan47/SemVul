FreeImage_ZLibCompress(BYTE *target, DWORD target_size, BYTE *source, DWORD source_size) {
	uLongf dest_len = (uLongf)target_size;

	int zerr = compress(target, &dest_len, source, source_size);
	switch(zerr) {
		case Z_MEM_ERROR:
		case Z_BUF_ERROR:
			FreeImage_OutputMessageProc(FIF_UNKNOWN, "Zlib error : %s", zError(zerr));
			return 0;
		case Z_OK:
			return dest_len;
	}

	return 0;
}
