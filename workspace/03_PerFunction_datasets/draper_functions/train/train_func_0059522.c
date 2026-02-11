unpermute_stars_tagalong(startree_t* treein,
							 fitstable_t* tagout) {
	fitstable_t* tagin;
	qfits_header* tmphdr;
	int N;
	tagin = startree_get_tagalong(treein);
	if (!tagin) {
		ERROR("No input tag-along table");
		return -1;
	}
	N = startree_N(treein);
	assert(fitstable_nrows(tagin) == N);
	fitstable_clear_table(tagin);
	fitstable_add_fits_columns_as_struct(tagin);
	fitstable_copy_columns(tagin, tagout);
	tmphdr = tagout->header;
	tagout->header = tagin->header;
	if (fitstable_write_header(tagout)) {
		ERROR("Failed to write tag-along table header");
		return -1;
	}
	if (fitstable_copy_rows_data(tagin, (int*)treein->tree->perm, N, tagout)) {
		ERROR("Failed to copy tag-along table rows from input to output");
		return -1;
	}
	if (fitstable_fix_header(tagout)) {
		ERROR("Failed to fix tag-along table header");
		return -1;
	}
	tagout->header = tmphdr;
	return 0;
}
