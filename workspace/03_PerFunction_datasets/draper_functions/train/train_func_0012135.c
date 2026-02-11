open_native_db_files (const char *dname, FILE **f1, char *name1,
		      FILE **f2, char *name2)
{
    char dbbase[FILENAME_MAX];
    char fname[FILENAME_MAX];
    FILE *fidx = NULL, *fbin = NULL;
    int err = 0;

    if (dname != NULL) {
	strcpy(dbbase, dname);
    } else {
	strcpy(dbbase, saved_db_name);
    }

    if (has_suffix(dbbase, ".bin")) {
	dbbase[strlen(dbbase) - 4] = '\0';
    }

    if (f1 != NULL) {
	strcpy(fname, dbbase);
	strcat(fname, ".idx");

	if (name1 != NULL) {
	    err = gretl_write_access(fname);
	    if (!err) {
		strcpy(name1, fname);
	    }
	}

	if (!err) {
	    fidx = gretl_fopen(fname, "r");
	    if (fidx == NULL) {
		gretl_errmsg_set(_("Couldn't open database index file"));
		err = E_FOPEN;
	    }
	}
    }

    if (f2 != NULL && !err) {
	strcpy(fname, dbbase);
	strcat(fname, ".bin");

	if (name2 != NULL) {
	    err = gretl_write_access(fname);
	    if (!err) {
		strcpy(name2, fname);
	    }
	}

	if (!err) {
	    fbin = gretl_fopen(fname, "rb");
	    if (fbin == NULL) {
		gretl_errmsg_set(_("Couldn't open database binary file"));
		err = E_FOPEN;
	    }
	}
    }

    if (err) {
	if (fidx != NULL) {
	    fclose(fidx);
	}
    } else {
	if (f1 != NULL) {
	    *f1 = fidx;
	}
	if (f2 != NULL) {
	    *f2 = fbin;
	}
    }

    return err;
}
