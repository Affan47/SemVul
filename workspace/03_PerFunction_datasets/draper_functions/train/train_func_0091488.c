gog_dropbar_populate_editor (GogObject *obj,
			     GOEditor *editor,
                             GogDataAllocator *dalloc,
                             GOCmdContext *cc)
{
#ifdef GOFFICE_WITH_GTK
	GtkBuilder *gui =
		go_gtk_builder_load ("res:go:plot_barcol/gog-area-prefs.ui",
				    GETTEXT_PACKAGE, cc);
	if (gui != NULL) {
		GtkWidget *w = go_gtk_builder_get_widget (gui, "before-grid");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (w),
				(GOG_PLOT (obj))->rendering_order == GOG_PLOT_RENDERING_BEFORE_GRID);
		g_signal_connect (G_OBJECT (w),
			"toggled",
			G_CALLBACK (display_before_grid_cb), obj);
		w = go_gtk_builder_get_widget (gui, "gog-area-prefs");
		go_editor_add_page (editor, w, _("Properties"));
		g_object_unref (gui);
	}

#endif
	gog_dropbar_parent_klass->populate_editor (obj, editor, dalloc, cc);
}
