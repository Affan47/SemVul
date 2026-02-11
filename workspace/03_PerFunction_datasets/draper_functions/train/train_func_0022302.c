set_toolbar_style_for_position (GtkToolbar *tb, GtkPositionType pos)
{
	GtkWidget *box = gtk_widget_get_parent (GTK_WIDGET (tb));

	static const GtkOrientation orientations[] = {
		GTK_ORIENTATION_VERTICAL, GTK_ORIENTATION_VERTICAL,
		GTK_ORIENTATION_HORIZONTAL, GTK_ORIENTATION_HORIZONTAL
	};

	gtk_orientable_set_orientation (GTK_ORIENTABLE (tb),
					orientations[pos]);

	if (GTK_IS_HANDLE_BOX (box)) {
		static const GtkPositionType hdlpos[] = {
			GTK_POS_TOP, GTK_POS_TOP,
			GTK_POS_LEFT, GTK_POS_LEFT
		};

		gtk_handle_box_set_handle_position (GTK_HANDLE_BOX (box),
						    hdlpos[pos]);
	}
	if (pos == GTK_POS_TOP || pos == GTK_POS_BOTTOM)
		g_object_set (G_OBJECT (tb), "hexpand", TRUE, "vexpand", FALSE, NULL);
	else
		g_object_set (G_OBJECT (tb), "vexpand", TRUE, "hexpand", FALSE, NULL);
}
