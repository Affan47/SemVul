on_combobox2_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GtkWidget *w=lookup_widget(window1,"combobox1");
	guint sel = gtk_combo_box_get_active (combobox);

	if (sel > 4 ) return;
	if (sel < 0 ) return;
	gtk_widget_set_sensitive(w,(sel==3));

	if (sel < 3 ) {
		update_startend(sel);
		return;
	}
	if (sel == 4 ) {
		update_startend(UNIT_AUDIOFRAMES);
		return;
	} else {
		sel = gtk_combo_box_get_active (GTK_COMBO_BOX(w));
		if (sel+3 >= UNIT_LAST ) return;
		update_startend(4+ sel);
	}
}
