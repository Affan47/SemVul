fits_header_set_double(qfits_header* hdr, const char* key, double val,
                            const char* comment) {
	if (qfits_header_getstr(hdr, key))
		fits_header_mod_double(hdr, key, val, comment);
	else
		fits_header_add_double(hdr, key, val, comment);
}
