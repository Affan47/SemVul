local_path(gfarm_ino_t inum, gfarm_uint64_t gen, const char *diag,
	char **pathp)
{
	char *p;
	static int length = 0;
	static char template[] = "/data/00112233/44/55/66/778899AABBCCDDEEFF";
#define DIRLEVEL 5

	if (length == 0)
		length = strlen(gfarm_spool_root) + sizeof(template);

	GFARM_MALLOC_ARRAY(p, length);
	if (p == NULL) {
		fatal(GFARM_MSG_1000464, "%s: no memory for %d bytes",
			diag, length);
	}
	snprintf(p, length, "%s/data/%08X/%02X/%02X/%02X/%02X%08X%08X",
	    gfarm_spool_root,
	    (unsigned int)((inum >> 32) & 0xffffffff),
	    (unsigned int)((inum >> 24) & 0xff),
	    (unsigned int)((inum >> 16) & 0xff),
	    (unsigned int)((inum >>  8) & 0xff),
	    (unsigned int)( inum        & 0xff),
	    (unsigned int)((gen  >> 32) & 0xffffffff),
	    (unsigned int)( gen         & 0xffffffff));
	*pathp = p;
}
