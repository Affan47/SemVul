gedit_output_window_finalize (GObject *object)
{
	GeditOutputWindow *ow;

	ow = GEDIT_OUTPUT_WINDOW (object);

	if (ow->priv != NULL)
	{
		g_free (ow->priv);
	}

	G_OBJECT_CLASS (gedit_output_window_parent_class)->finalize (object);
}
