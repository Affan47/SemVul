ignore_dialog_callback(gpointer userdata, int response)
{
	struct contact *c = (struct contact *)userdata;

	if (response) {
		move_contact(_("Ignore"), c);
		update_contact_list();
		write_contact_list();
	}
}
