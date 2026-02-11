edit_person_entry_att_changed (GtkWidget *entry, gpointer data)
{
	gboolean non_empty = gtk_cmclist_get_row_data(GTK_CMCLIST(personEditDlg->clist_attrib), 0) != NULL;
	const gchar *sName;
	int index;

	if (personEditDlg->read_only)
		return;

	index = gtk_combo_box_get_active(GTK_COMBO_BOX(personEditDlg->entry_atname));
	sName = ATTRIBUTE[index];
	if (list_find_attribute(sName)) {
		gtk_widget_set_sensitive(personEditDlg->attrib_add,FALSE);
		gtk_widget_set_sensitive(personEditDlg->attrib_mod,non_empty);
		attrib_adding = FALSE;
		attrib_saving = non_empty;
	}
	else {
		gtk_widget_set_sensitive(personEditDlg->attrib_add,TRUE);
		gtk_widget_set_sensitive(personEditDlg->attrib_mod,non_empty);
		attrib_adding = TRUE;
		attrib_saving = non_empty;
	}
}
