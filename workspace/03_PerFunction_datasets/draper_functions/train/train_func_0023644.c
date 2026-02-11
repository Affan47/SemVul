startree_new() {
	startree_t* s = startree_alloc();
	s->header = qfits_header_default();
	if (!s->header) {
		fprintf(stderr, "Failed to create a qfits header for star kdtree.\n");
		free(s);
		return NULL;
	}
	qfits_header_add(s->header, "AN_FILE", AN_FILETYPE_STARTREE, "This file is a star kdtree.", NULL);
    s->writing = TRUE;
	return s;
}
