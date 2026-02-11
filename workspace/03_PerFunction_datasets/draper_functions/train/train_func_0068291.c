gconf_cell_renderer_finalize (GObject *object)
{
	GConfCellRenderer *renderer = GCONF_CELL_RENDERER (object);

	if (renderer->value)
		gconf_value_free (renderer->value);

	g_object_unref (renderer->text_renderer);
	g_object_unref (renderer->toggle_renderer);

	(* G_OBJECT_CLASS (gconf_cell_renderer_parent_class)->finalize) (object);
}
