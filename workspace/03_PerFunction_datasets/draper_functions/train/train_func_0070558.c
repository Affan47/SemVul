autodetect_file_open_mode(const char *filename)
{
#define AUTODETECT_SIZE	128
	FILE *f=fopen(filename, "rb");
	uint r=FOM_BIN;
	if (f) {
		byte buf[AUTODETECT_SIZE];
		int c=fread(buf, 1, AUTODETECT_SIZE, f);

		if (!c) return FOM_TEXT;
		bool is_bin=false;
		uint prob_bin_chars=0;
		for (int i=0; i<c; i++) {
			if (buf[i]==0) {
				is_bin=true;
				break;
			} else if (buf[i]<32) {
				prob_bin_chars++;
			} else if (buf[i]>0xa9) {
				prob_bin_chars++;
			}
		}
		if (c) {
			if (prob_bin_chars*100/c>=50) is_bin=true;
		} else is_bin=true;
		if (!is_bin) r=FOM_TEXT;
		fclose(f);
		return r;
	}
	return FOM_BIN;
}
