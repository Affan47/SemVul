merge_index(quadfile* quad, codetree* code, startree_t* star,
				const char* indexfn) {
    FILE* fout;
	fitstable_t* tag = NULL;

    fout = fopen(indexfn, "wb");
    if (!fout) {
        SYSERROR("Failed to open output file");
        return -1;
    }

	if (quadfile_write_header_to(quad, fout)) {
		ERROR("Failed to write quadfile header to index file %s", indexfn);
		return -1;
	}
	if (quadfile_write_all_quads_to(quad, fout)) {
		ERROR("Failed to write quads to index file %s", indexfn);
		return -1;
	}
	if (fits_pad_file(fout)) {
		ERROR("Failed to pad index file %s", indexfn);
		return -1;
	}

	if (codetree_append_to(code, fout)) {
		ERROR("Failed to write code kdtree to index file %s", indexfn);
		return -1;
	}
	if (fits_pad_file(fout)) {
		ERROR("Failed to pad index file %s", indexfn);
		return -1;
	}

	if (startree_append_to(star, fout)) {
		ERROR("Failed to write star kdtree to index file %s", indexfn);
		return -1;
	}
	if (fits_pad_file(fout)) {
		ERROR("Failed to pad index file %s", indexfn);
		return -1;
	}

	if (startree_has_tagalong(star))
		tag = startree_get_tagalong(star);
	if (tag) {
		if (fitstable_append_to(tag, fout)) {
			ERROR("Failed to write star kdtree tag-along data to index file %s", indexfn);
			return -1;
		}
		if (fits_pad_file(fout)) {
			ERROR("Failed to pad index file %s", indexfn);
			return -1;
		}
	}

    if (fclose(fout)) {
        SYSERROR("Failed to close index file %s", indexfn);
        return -1;
    }
	return 0;
}
