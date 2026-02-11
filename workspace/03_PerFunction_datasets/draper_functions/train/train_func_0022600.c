annotation_get_fromfile(const char *int_mboxname __attribute__((unused)),
				    const char *ext_mboxname,
				    const char *entry,
				    struct fetchdata *fdata,
				    struct mailbox_annotation_rock *mbrock __attribute__((unused)),
				    void *rock)
{
    const char *filename = (const char *) rock;
    char path[MAX_MAILBOX_PATH+1], buf[MAX_MAILBOX_PATH+1], *p;
    FILE *f;
    struct stat statbuf;
    struct annotation_data attrib;

    snprintf(path, sizeof(path), "%s/msg/%s", config_dir, filename);
    if ((f = fopen(path, "r")) && fgets(buf, sizeof(buf), f)) {
	if ((p = strchr(buf, '\r'))!=NULL) *p = 0;
	if ((p = strchr(buf, '\n'))!=NULL) *p = 0;

	memset(&attrib, 0, sizeof(attrib));

	attrib.value = buf;
	attrib.size = strlen(buf);
	attrib.contenttype = "text/plain";
	if (!fstat(fileno(f), &statbuf))
	    attrib.modifiedsince = statbuf.st_mtime;

	output_entryatt(ext_mboxname, entry, "", &attrib, fdata);
    }
    if (f) fclose(f);
}
