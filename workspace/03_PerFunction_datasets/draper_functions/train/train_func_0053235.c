append_error(const char *fmt, ...)
{
    FILE *fp = NULL;
    char *work = NULL;
    int count = 0;
    va_list ap;

    va_start(ap, fmt);
    if ((fp = tmpfile())) {
	count = vfprintf(fp, fmt, ap);
	if (count >= 0 && (work = G_calloc(count + 1, 1))) {
	    rewind(fp);
	    fread(work, 1, count, fp);
	    db_append_string(errMsg, work);
	    G_free(work);
	}
	fclose(fp);
    }
    va_end(ap);
}
