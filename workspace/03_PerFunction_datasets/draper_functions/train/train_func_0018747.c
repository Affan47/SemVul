gretl_rename (const char *oldpath, const char *newpath)
{
    gchar *oldconv = NULL, *newconv = NULL;
    int err;

    gretl_error_clear();

    err = maybe_recode_path(oldpath, stdio_use_utf8, &oldconv);

    if (!err) {
	err = maybe_recode_path(newpath, stdio_use_utf8, &newconv);
    }

    if (!err) {
	if (oldconv == NULL && newconv == NULL) {
	    err = rename(oldpath, newpath);
	} else if (oldconv != NULL && newconv != NULL) {
	    err = rename(oldconv, newconv);
	} else if (oldconv != NULL) {
	    err = rename(oldconv, newpath);
	} else if (newconv != NULL) {
	    err = rename(oldpath, newconv);
	}
    }

#if 0
    fprintf(stderr, "oldpath='%s'\nnewpath='%s'\n"
	    "err=%d\n", oldpath, newpath, err);
#endif

    if (oldconv != NULL || newconv != NULL) {
	g_free(oldconv);
	g_free(newconv);
    }

    if (errno != 0) {
	gretl_errmsg_set_from_errno("gretl_rename");
    }

    return err;
}
