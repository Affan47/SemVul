md5_one(const char *fn)
{
	unsigned char buf[4096], digest[16];
	MD5_CTX md5;
	int l;
	FILE *fp;

	fp = strcmp(fn, "-")? fopen(fn, "r") : stdin;
	if (fp == 0) {
		fprintf(stderr, "md5sum: %s: No such file or directory\n", fn);
		exit(1);
	}
	MD5Init(&md5);
	while ((l = fread(buf, 1, 4096, fp)) > 0)
		MD5Update(&md5, buf, l);
	MD5Final(digest, &md5);
	if (fp != stdin) fclose(fp);
	for (l = 0; l < 16; ++l)
		printf("%c%c", HEX_STR[digest[l]>>4&0xf], HEX_STR[digest[l]&0xf]);
	printf("  %s\n", fn);
}
