EXPremove(p, size)
    char		*p;
    long		*size;
{
    register char	*q;
    struct stat		Sb;


    for (q = p; *q; q++)
	if (*q == '.')
	    *q = '/';
    if (EXPsizing && *size < 0 && stat(p, &Sb) >= 0)
	*size = (int)(((long)Sb.st_size >> 10) + (((long)Sb.st_size >> 9) & 1));

    if (EXPverbose > 1)
	(void)printf("\tunlink %s\n", p);
    EXPunlinked++;

    if (EXPtracing) {
	(void)printf("%s\n", p);
	return;
    }
    if (EXPunlinkfile) {
	(void)fprintf(EXPunlinkfile, "%s\n", p);
	if (!ferror(EXPunlinkfile))
	    return;
	(void)fprintf(stderr, "Can't write to -z file, %s\n",
		strerror(errno));
	(void)fprintf(stderr, "(Will ignore it for rest of run.)\n");
	(void)fclose(EXPunlinkfile);
	EXPunlinkfile = NULL;
    }
    if (unlink(p) < 0 && errno != ENOENT)
	(void)fprintf(stderr, "Can't unlink %s, %s\n", p, strerror(errno));
}
