write_gretl_R_files (const char *buf,
			 const DATASET *dset,
			 gretlopt opt)
{
    int err = 0;

#if FDEBUG
    printf("write_gretl_R_files: starting\n");
#endif

    make_gretl_R_names();


    err = write_gretl_R_profile(opt);
    if (err) {
	fprintf(stderr, "error writing gretl.Rprofile\n");
    }

    if (!err) {

	err = write_R_source_file(buf, dset, opt);
	if (err) {
	    fprintf(stderr, "error writing gretl's Rsrc\n");
	}
    }

#if FDEBUG
    printf("write_gretl_R_files: returning %d\n", err);
#endif

    return err;
}
