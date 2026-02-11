gog_xyz_plot_populate_editor (GogObject *item,
				  GOEditor *editor,
				  G_GNUC_UNUSED GogDataAllocator *dalloc,
				  GOCmdContext *cc)
{
	if (!GOG_XYZ_PLOT (item)->data_xyz) {
		GtkWidget *w = gog_xyz_plot_pref (GOG_XYZ_PLOT (item), cc);
		go_editor_add_page (editor, w, _("Properties"));
		g_object_unref (w);
	}

	(GOG_OBJECT_CLASS (plot_xyz_parent_klass)->populate_editor) (item, editor, dalloc, cc);
}
