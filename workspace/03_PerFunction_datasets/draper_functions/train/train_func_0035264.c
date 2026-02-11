on_equip_shape_changed
	(
	GtkWidget *widget,
	gpointer data
	)
	{
	Equip_row_widgets *eq = (Equip_row_widgets *) data;
	ExultStudio *studio = ExultStudio::get_instance();
	studio->show_equip_shape(eq);
	int shape = gtk_spin_button_get_value_as_int(
				GTK_SPIN_BUTTON(eq->shape));
	const char *nm = studio->get_shape_name(shape);
	gtk_label_set_text(GTK_LABEL(eq->name), nm ? nm : "");
	return (TRUE);
	}
