startree_close(startree_t* s) {
	if (!s) return 0;
	if (s->inverse_perm)
		free(s->inverse_perm);
 	if (s->header)
		qfits_header_destroy(s->header);
    if (s->tree) {
        if (s->writing) {
            kdtree_free(s->tree);
			free(s->sweep);
		}
        else
            kdtree_fits_close(s->tree);
    }
	if (s->tagalong)
		fitstable_close(s->tagalong);
	free(s);
	return 0;
}
