pgd_render_create_widget (PopplerDocument *document)
{
	PgdRenderDemo *demo;
	GtkWidget     *vbox, *hbox;

	demo = g_new0 (PgdRenderDemo, 1);

	demo->doc = g_object_ref (document);
	demo->scale = 1.0;

	vbox = gtk_vbox_new (FALSE, 6);

	hbox = pgd_render_properties_selector_create (demo);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 6);
	gtk_widget_show (hbox);

	demo->darea = gtk_drawing_area_new ();
	g_signal_connect (G_OBJECT (demo->darea), "expose_event",
			  G_CALLBACK (pgd_render_drawing_area_expose),
			  (gpointer)demo);

	demo->swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (demo->swindow),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (demo->swindow),
					       demo->darea);
	gtk_widget_show (demo->darea);

	gtk_box_pack_start (GTK_BOX (vbox), demo->swindow, TRUE, TRUE, 0);
	gtk_widget_show (demo->swindow);

	g_object_weak_ref (G_OBJECT (demo->swindow),
			   (GWeakNotify)pgd_render_free,
			   (gpointer)demo);

	return vbox;
}
