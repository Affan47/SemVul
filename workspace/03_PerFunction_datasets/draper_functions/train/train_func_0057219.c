create_control_for_size (GthFilter *filter)
{
	GtkWidget *control;
	GtkWidget *limit_label;
	int        i, size_idx;
	gboolean   size_set = FALSE;

	control = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);


	limit_label = gtk_label_new_with_mnemonic (_("_Limit to"));
	gtk_widget_show (limit_label);


	filter->priv->limit_spinbutton = gtk_spin_button_new_with_range (0, G_MAXINT, 1.0);
	gtk_spin_button_set_digits (GTK_SPIN_BUTTON (filter->priv->limit_spinbutton), 1);
	gtk_widget_show (filter->priv->limit_spinbutton);
	gtk_label_set_mnemonic_widget (GTK_LABEL (limit_label), filter->priv->limit_spinbutton);


	filter->priv->size_combo_box = gtk_combo_box_text_new ();
	gtk_widget_show (filter->priv->size_combo_box);

	size_idx = 0;
	for (i = 0; i < G_N_ELEMENTS (size_data); i++) {
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (filter->priv->size_combo_box),
						_(size_data[i].name));
		if (! size_set && ((i == G_N_ELEMENTS (size_data) - 1) || (filter->priv->limit < size_data[i + 1].size))) {
			size_idx = i;
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (filter->priv->limit_spinbutton), (double) filter->priv->limit / size_data[i].size);
			size_set = TRUE;
		}
	}
	gtk_combo_box_set_active (GTK_COMBO_BOX (filter->priv->size_combo_box), size_idx);

	g_signal_connect (G_OBJECT (filter->priv->size_combo_box),
			  "changed",
			  G_CALLBACK (size_combo_box_changed_cb),
			  filter);

	g_signal_connect (G_OBJECT (filter->priv->limit_spinbutton),
			  "value-changed",
			  G_CALLBACK (size_limit_spinbutton_changed_cb),
			  filter);


	gtk_box_pack_start (GTK_BOX (control), limit_label, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (control), filter->priv->limit_spinbutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (control), filter->priv->size_combo_box, FALSE, FALSE, 0);

	return control;
}
