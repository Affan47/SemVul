find_table_column(fitsbin_t* fb, const char* colname, off_t* pstart, off_t* psize, int* pext) {
    int i;
	for (i=1; i<fb->Next; i++) {
        int c;
        const qfits_table* table = fitsbin_get_table_const(fb, i);
		if (!table)
			continue;
		c = fits_find_column(table, colname);
		if (c == -1)
			continue;
		if (fitsbin_get_datinfo(fb, i, pstart, psize)) {
			ERROR("error getting start/size for ext %i in file %s.\n", i, fb->filename);
            return -1;
        }
		if (pext) *pext = i;
		return 0;
    }
	debug("searched %i extensions in file %s but didn't find a table with a column \"%s\".\n",
		  fb->Next, fb->filename, colname);
    return -1;
}
