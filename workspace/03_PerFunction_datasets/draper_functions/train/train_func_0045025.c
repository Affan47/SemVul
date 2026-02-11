open_binfile (const char *dbbase, int code, int offset, int *err)
{
    char dbbin[MAXLEN];
    FILE *fp = NULL;

    strcpy(dbbin, dbbase);
    if (code == GRETL_NATIVE_DB) {
	if (strstr(dbbin, ".bin") == NULL) {
	    strcat(dbbin, ".bin");
	}
    } else {
	if (strstr(dbbin, ".bn7") == NULL) {
	    strcat(dbbin, ".bn7");
	}
    }

    fp = gretl_fopen(dbbin, "rb");

    if (fp == NULL) {
	*err = E_FOPEN;
    } else if (fseek(fp, (long) offset, SEEK_SET)) {
	*err = DB_PARSE_ERROR;
	fclose(fp);
	fp = NULL;
    }

    return fp;
}
