preview_grid_dispose (GObject *obj)
{
	GnmPreviewGrid *pg = GNM_PREVIEW_GRID (obj);

	if (pg->defaults.style != NULL) {
		gnm_style_unref (pg->defaults.style);
		pg->defaults.style = NULL;
	}
	value_release (pg->defaults.value);
	pg->defaults.value = NULL;

	g_clear_object (&pg->sheet);

	G_OBJECT_CLASS (parent_klass)->dispose (obj);
}
