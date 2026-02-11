load_zipped_file (int pathtype, int pathindex, const char* zipfile, const char* filename, unsigned char** buf, unsigned int* length) {
	ZIP* zip;
	struct zipent* ent;

	zip = cache_openzip(pathtype, pathindex, zipfile);
	if (!zip)
		return -1;

	while (readzip(zip)) {

		char crc[9];

		ent = &(zip->ent);

		sprintf(crc,"%08x",ent->crc32);
		if (equal_filename(ent->name, filename) ||
				(ent->crc32 && !strcmp(crc, filename)))
		{
			*length = ent->uncompressed_size;
			*buf = (unsigned char*)malloc( *length );
			if (!*buf) {
				if (!gUnzipQuiet)
					printf("load_zipped_file(): Unable to allocate %d bytes of RAM\n",*length);
				cache_closezip(zip);
				return -1;
			}

			if (readuncompresszip(zip, ent, (char*)*buf)!=0) {
				free(*buf);
				cache_closezip(zip);
				return -1;
			}

			cache_suspendzip(zip);
			return 0;
		}
	}

	cache_suspendzip(zip);
	return -1;
}
