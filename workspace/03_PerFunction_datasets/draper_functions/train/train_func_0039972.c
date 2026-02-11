popup_activate_email (ENameSelectorEntry *name_selector_entry,
                      GtkWidget *menu_item)
{
	EDestination *destination;
	EContact     *contact;
	gint          email_num;

	destination = e_name_selector_entry_get_popup_destination (name_selector_entry);
	if (!destination)
		return;

	contact = e_destination_get_contact (destination);
	if (!contact)
		return;

	email_num = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (menu_item), "order"));
	e_destination_set_contact (destination, contact, email_num);
}
