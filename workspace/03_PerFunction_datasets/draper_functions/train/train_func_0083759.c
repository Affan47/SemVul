xylist_open(const char* fn) {
    qfits_header* hdr;
	xylist_t* ls = NULL;
	ls = xylist_new();
	if (!ls) {
        ERROR("Failed to allocate xylist");
		return NULL;
    }
    ls->table = fitstable_open_mixed(fn);
    if (!ls->table) {
		ERROR("Failed to open FITS table %s", fn);
        free(ls);
        return NULL;
    }
    ls->table->extension = 1;

    hdr = fitstable_get_primary_header(ls->table);
	ls->antype = fits_get_dupstring(hdr, "AN_FILE");

	ls->nfields = fitstable_n_extensions(ls->table) - 1;
    ls->include_flux = TRUE;
    ls->include_background = TRUE;
	assert(is_reading(ls));
	return ls;
}
