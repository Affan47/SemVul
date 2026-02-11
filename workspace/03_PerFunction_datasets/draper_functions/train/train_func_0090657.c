gnm_notebook_button_finalize (GObject *obj)
{
	GnmNotebookButton *nbb = GNM_NOTEBOOK_BUTTON (obj);
	g_clear_object (&nbb->layout);
	g_clear_object (&nbb->layout_active);
	gdk_rgba_free (nbb->fg);
	gdk_rgba_free (nbb->bg);
	gnm_notebook_button_parent_class->finalize (obj);
}
