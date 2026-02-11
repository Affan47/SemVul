read_pcx(FILE * handle, void *buf, int buf_len, char *pal)
{
	unsigned char *buffer=buf;
	short c1;
	short a, b;
	long ofs1;
	if (buffer != 0) {
		fseek(handle, 128, SEEK_CUR);
		ofs1 = 0;
		while (ofs1 < buf_len) {
			a = fgetc(handle);
			if ((a & 0xc0) == 0xc0) {
				b = fgetc(handle);
				a &= 0x3f;
				for (c1 = 0; c1 < a && ofs1 < buf_len; c1++)
					buffer[ofs1++] = (char) b;
			} else
				buffer[ofs1++] = (char) a;
		}
		if (pal != 0) {
			fseek(handle, 1, SEEK_CUR);
			for (c1 = 0; c1 < 768; c1++)
				pal[c1] = fgetc(handle) >> 2;
		}
	}
}
