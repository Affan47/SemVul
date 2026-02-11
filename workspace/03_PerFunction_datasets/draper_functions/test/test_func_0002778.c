test_and_fetch(const char *fn)
{
	FILE *fp;
	if (strstr(fn, "ftp://") == fn || strstr(fn, "http://") == fn) {
#ifdef _USE_KETFILE
		const int buf_size = 1 * 1024 * 1024;
		knetFile *fp_remote;
		uint8_t *buf;
		const char *p;
		for (p = fn + strlen(fn) - 1; p >= url; --p)
			if (*p == '/') break;
		++p;
		if ((fp_remote = knet_open(fn, "r")) == 0) {
			if (hts_verbose >= 1) fprintf(stderr, "[E::%s] fail to open remote file\n", __func__);
			return 0;
		}
		if ((fp = fopen(fn, "w")) == 0) {
			if (hts_verbose >= 1) fprintf(stderr, "[E::%s] fail to create file in the working directory\n", __func__);
			knet_close(fp_remote);
			return 0;
		}
		if (hts_verbose >= 3) fprintf(stderr, "[M::%s] downloading file '%s' to local directory\n", __func__, fn);
		buf = (uint8_t*)calloc(buf_size, 1);
		while ((l = knet_read(fp_remote, buf, buf_size)) != 0) fwrite(buf, 1, l, fp);
		free(buf);
		fclose(fp);
		knet_close(fp_remote);
		return (char*)p;
#else
		return 0;
#endif
	} else {
		if ((fp = fopen(fn, "rb")) == 0) return 0;
		fclose(fp);
		return (char*)fn;
	}
}
