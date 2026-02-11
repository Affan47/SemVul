usnob_fits_open(char* fn) {
	usnob_fits* cat = NULL;
    cat = fitstable_open(fn);
    if (!cat)
        return NULL;
    add_columns(cat, FALSE);
    fitstable_use_buffered_reading(cat, sizeof(usnob_entry), 1000);
    cat->postprocess_read_structs = postprocess_read_structs;
    if (fitstable_read_extension(cat, 1)) {
        fprintf(stderr, "usnob-fits: table in extension 1 didn't contain the required columns.\n");
        fprintf(stderr, "  missing: ");
        fitstable_print_missing(cat, stderr);
        fprintf(stderr, "\n");
        usnob_fits_close(cat);
        return NULL;
    }
	return cat;
}
