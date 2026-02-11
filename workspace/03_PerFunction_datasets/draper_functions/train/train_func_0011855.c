file_base64_file_action(
				struct stat& finfo,
				int f,
				const String&, const char* , bool,
				void *context) {

	if(finfo.st_size) {
		File_base64_action_info& info=*static_cast<File_base64_action_info *>(context);
		*info.base64=new(PointerFreeGC) unsigned char[finfo.st_size * 2 + 6];
		unsigned char* base64 = *info.base64;
		int state=0;
		int save=0;
		int nCount;
		do {
			unsigned char buffer[FILE_BUFFER_SIZE];
			nCount = file_block_read(f, buffer, sizeof(buffer));
			if( nCount ){
				size_t filled=g_mime_utils_base64_encode_step ((const unsigned char*)buffer, nCount, base64, &state, &save);
				base64+=filled;
			}
		} while(nCount > 0);
		g_mime_utils_base64_encode_close (0, 0, base64, &state, &save);
	}
}
