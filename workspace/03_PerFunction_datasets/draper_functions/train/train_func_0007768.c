check_existing_file(char *base_file, char *ext, char *data, u32 data_size, u32 idx)
{
	char szFile[GF_MAX_PATH];
	u64 fsize;
	FILE *f;

	sprintf(szFile, "%s%04X%s", base_file, idx, ext);

	f = gf_f64_open(szFile, "rb");
	if (!f) return 0;

	gf_f64_seek(f, 0, SEEK_END);
	fsize = gf_f64_tell(f);
	if (fsize==data_size) {
		u32 offset=0;
		char cache[1024];
		gf_f64_seek(f, 0, SEEK_SET);
		while (fsize) {
			u32 read = fread(cache, 1, 1024, f);
			fsize -= read;
			if (memcmp(cache, data+offset, sizeof(char)*read)) break;
			offset+=read;
		}
		fclose(f);
		f = NULL;

		if (!fsize) return 2;
	}
	if (f)
	  fclose(f);
	return 1;
}
