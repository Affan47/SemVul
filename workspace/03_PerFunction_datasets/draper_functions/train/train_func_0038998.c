eel_canvas_accessible_initialize (AtkObject *obj,
				  gpointer   data)
{
	EelCanvas *canvas = data;

	if (ATK_OBJECT_CLASS (accessible_parent_class)->initialize != NULL) {
		ATK_OBJECT_CLASS (accessible_parent_class)->initialize (obj, data);
	}

	gtk_accessible_set_widget (GTK_ACCESSIBLE (obj), GTK_WIDGET (data));
	g_signal_connect (gtk_scrollable_get_hadjustment (GTK_SCROLLABLE (canvas)),
			  "value-changed",
			  G_CALLBACK (eel_canvas_accessible_adjustment_changed),
			  obj);
	g_signal_connect (gtk_scrollable_get_vadjustment (GTK_SCROLLABLE (canvas)),
			  "value-changed",
			  G_CALLBACK (eel_canvas_accessible_adjustment_changed),
			  obj);

	obj->role = ATK_ROLE_LAYERED_PANE;
}
