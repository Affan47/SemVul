user_init(const char *str)
{
    char *contents;
    char line[BUFSIZ];
    FILE *fp;
    struct stat statbuf;
    int saw_bb, must_inline, rc;
    int lx, ly, ux, uy;
    usershape_t *us;

    if (!EPSF_contents)
	EPSF_contents = dtopen(&ImageDictDisc, Dtoset);

    us = dtmatch(EPSF_contents, str);
    if (us)
	return us;

    if (!(fp = fopen(str, "r"))) {
	agerr(AGWARN, "couldn't open epsf file %s\n", str);
	return NULL;
    }

    saw_bb = must_inline = FALSE;
    while (fgets(line, sizeof(line), fp)) {
	if (sscanf
	    (line, "%%%%BoundingBox: %d %d %d %d", &lx, &ly, &ux, &uy) == 4) {
	    saw_bb = TRUE;
	}
	if ((line[0] != '%') && strstr(line,"read")) must_inline = TRUE;
	if (saw_bb && must_inline) break;
    }

    if (saw_bb) {
	us = GNEW(usershape_t);
	us->x = lx;
	us->y = ly;
	us->w = ux - lx;
	us->y = uy - ly;
	us->name = str;
	us->macro_id = N_EPSF_files++;
	fstat(fileno(fp), &statbuf);
	contents = us->data = N_GNEW(statbuf.st_size + 1, char);
	fseek(fp, 0, SEEK_SET);
	rc = fread(contents, statbuf.st_size, 1, fp);
	contents[statbuf.st_size] = '\0';
	dtinsert(EPSF_contents, us);
	us->must_inline = must_inline;
    } else {
	agerr(AGWARN, "BoundingBox not found in epsf file %s\n", str);
	us = NULL;
    }
    fclose(fp);
    return us;
}
