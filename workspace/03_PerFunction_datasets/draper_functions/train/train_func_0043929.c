go_combo_pixmaps_finalize (GObject *object)
{
	GOComboPixmaps *combo = GO_COMBO_PIXMAPS (object);

	g_clear_object (&combo->grid);

	if (combo->elements) {
		g_array_free (combo->elements, TRUE);
		combo->elements = NULL;
	}

	go_combo_pixmaps_parent_class->finalize (object);
}
