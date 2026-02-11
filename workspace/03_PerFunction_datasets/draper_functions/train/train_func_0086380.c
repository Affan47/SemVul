sge_register_pixbuf (GdkPixbuf * pixbuf, int index)
{
	int i;

	if (index == -1) {
		for (i = 0; i < gi_nb_pixbufs; i++)
			if (g_pixbufs[i] == 0)
				break;
		if (i == gi_nb_pixbufs) {
			gi_nb_pixbufs++;
			g_pixbufs =
			    (GdkPixbuf **) g_realloc (g_pixbufs,
						      sizeof (GdkPixbuf *)
						      * gi_nb_pixbufs);
		}
		g_pixbufs[i] = pixbuf;
	} else {
		i = index;
		g_object_unref (g_pixbufs[i]);
		g_pixbufs[i] = pixbuf;
		g_list_foreach (g_object_list, pixbuf_update_notify,
				(void *) &i);
	}

	return i;
}
