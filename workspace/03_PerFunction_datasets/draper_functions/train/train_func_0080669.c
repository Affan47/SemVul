gm_pixbuf_get_at_size(const gchar *filename, int width, int height) {
	GdkPixbuf *pix;
	GList *elem;
	GmPixbufInfo *i;

	if (filename == NULL || *filename == '\0') {
		return NULL;
	}

	for (elem = gm_pixbufs; elem; elem = elem->next) {
		i = (GmPixbufInfo *) (elem->data);

		if (strcmp(i->name, filename) == 0 &&
			i->width == width && i->height == height) {
			return i->pixbuf;
		}
	}


	pix = gm_pixbuf_create(filename, width, height);

	if (pix) {
		i = g_new(GmPixbufInfo, 1);
		i->name = g_strdup(filename);
		i->width = width;
		i->height = height;
		i->pixbuf = pix;
		gm_pixbufs = g_list_append(gm_pixbufs, i);
		return pix;
	} else {
		return NULL;
	}
}
