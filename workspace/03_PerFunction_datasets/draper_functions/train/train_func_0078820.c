cb_combo_selection_changed (SheetWidgetListBase *swl,
			    GtkComboBox *combo)
{
	int pos = swl->selection - 1;
	if (pos < 0) {
		gtk_entry_set_text (GTK_ENTRY (gtk_bin_get_child (GTK_BIN (combo))), "");
		pos = -1;
	}
	gtk_combo_box_set_active (combo, pos);
}
