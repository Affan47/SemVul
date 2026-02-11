gretl_read_foreign_data (const char *fname, GretlFileType file_type,
			     DATASET *dset, PRN *prn)
{
    int err = 0;

    if (fname == NULL || dset == NULL) {
	err = E_INVARG;
    } else if (dset->Z != NULL) {
	fprintf(stderr, "gretl_read_foreign_data: Z must be NULL on entry\n");
	err = E_INVARG;
    } if (file_type == GRETL_CSV) {
	err = import_csv(fname, dset, OPT_NONE, prn);
    } else if (SPREADSHEET_IMPORT(file_type)) {
	err = import_spreadsheet(fname, file_type, NULL, NULL,
				 dset, OPT_NONE, prn);
    } else if (OTHER_IMPORT(file_type)) {
	err = import_spreadsheet(fname, file_type, NULL, NULL,
				 dset, OPT_NONE, prn);
    } else {
	gretl_errmsg_set("Unknown data import type");
	err = E_INVARG;
    }

    return err;
}
