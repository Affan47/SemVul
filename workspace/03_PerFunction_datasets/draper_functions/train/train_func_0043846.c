load_xfile(xfile *xf, int verb) {
	FILE *fp;
	int i, nfiles;
	unsigned char *ibuf;
	unsigned long ilen, bread;

	if (verb) { printf("Loading file '%s'..",xf->name); fflush(stdout); }


#if !defined(O_CREAT) && !defined(_O_CREAT)
# error "Need to #include fcntl.h!"
#endif
#if defined(O_BINARY) || defined(_O_BINARY)
	if ((fp = fopen(xf->name,"rb")) == NULL)
#else
	if ((fp = fopen(xf->name,"r")) == NULL)
#endif
	{
		if (verb) printf("fopen '%s' failed\n",xf->name);
		return 1;
	}


	if (fseek(fp, 0, SEEK_END)) {
		if (verb) printf("fseek to EOF of '%s' failed\n",xf->name);
		return 1;
	}

	ilen = (unsigned long)ftell(fp);

	if (verb > 1) printf("Size of file '%s' is %ld bytes\n",xf->name, ilen);

	if (fseek(fp, 0, SEEK_SET)) {
		if (verb) printf("fseek to SOF of file '%s' failed\n",xf->name);
		return 1;
	}

	if ((ibuf = (unsigned char *)malloc(ilen)) == NULL)
		error("\nmalloc buffer for file '%s' failed",xf->name);

	if (verb > 1) printf("(Reading file '%s')\n",xf->name);

	if ((bread = fread(ibuf, 1, ilen, fp)) != ilen) {
		if (verb) printf("Failed to read file '%s', read %ld out of %ld bytes\n",xf->name,bread,ilen);
		return 1;
	}

	fclose(fp);

	if (xf->buf != NULL)
		free(xf->buf);
	xf->buf = ibuf;
	xf->len = ilen;

	if (verb) printf("done\n");

	return 0;
}
