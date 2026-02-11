grab_tagalong_data(startree_t* starkd, MatchObj* mo, blind_t* bp,
							   const int* starinds, int N) {
	fitstable_t* tagalong;
	int i;
	tagalong = startree_get_tagalong(starkd);
	if (!tagalong) {
		ERROR("Failed to find tag-along table in index");
		return FALSE;
	}
	if (!mo->tagalong)
		mo->tagalong = bl_new(16, sizeof(tagalong_t));

	if (bp->rdls_tagalong_all) {
		char* cols;

		bp->rdls_tagalong = fitstable_get_fits_column_names(tagalong, bp->rdls_tagalong);
		cols = sl_join(bp->rdls_tagalong, ", ");
		logverb("Found tag-along columns: %s\n", cols);
		free(cols);

		sl_remove_duplicates(bp->rdls_tagalong);
		cols = sl_join(bp->rdls_tagalong, ", ");
		logverb("After removing duplicates: %s\n", cols);
		free(cols);
	}
	for (i=0; i<sl_size(bp->rdls_tagalong); i++) {
		const char* col = sl_get(bp->rdls_tagalong, i);
		tagalong_t tag;
		if (fitstable_find_fits_column(tagalong, col, &(tag.units), &(tag.type), &(tag.arraysize))) {
			ERROR("Failed to find column \"%s\" in index", col);
			continue;
		}
		tag.data = fitstable_read_column_array_inds(tagalong, col, tag.type, starinds, N, NULL);
		if (!tag.data) {
			ERROR("Failed to read data for column \"%s\" in index", col);
			continue;
		}
		tag.name = strdup(col);
		tag.units = strdup(tag.units);
		tag.itemsize = fits_get_atom_size(tag.type) * tag.arraysize;
		tag.Ndata = N;
		bl_append(mo->tagalong, &tag);
	}
	return TRUE;
}
