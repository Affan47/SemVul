dbtext_get_password(void *handle, const char *qpw, const char *key,
		    char **ppass)
{
    dico_url_t url = handle;
    char *dir = dico_url_full_path(url);
    char *full_name;
    FILE *fp = open_file(dir, qpw, &full_name);
    int rc;

    if (fp) {
	char *buf = NULL;
	size_t size = 0;
	char *val = find_key(fp, key, &buf, &size);
	if (val)
	    *ppass = xstrdup(val);
	else
	    *ppass = NULL;
	fclose(fp);
	free(full_name);
	free(buf);
	rc = 0;
    } else
	rc = 1;
    free(dir);
    return rc;
}
