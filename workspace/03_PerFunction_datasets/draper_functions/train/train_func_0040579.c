gog_box_plot_finalize (GObject *obj)
{
	GogBoxPlot *plot = GOG_BOX_PLOT (obj);
	if (plot && plot->names)
		g_free (plot->names);
	G_OBJECT_CLASS (gog_box_plot_parent_klass)->finalize (obj);
}
