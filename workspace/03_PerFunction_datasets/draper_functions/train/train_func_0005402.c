mg_dialog_button_cb (GtkWidget *wid, char *cmd)
{

	char buf[128];
	char *host = "";
	char *topic;

	if (!current_sess)
		return;

	topic = (char *)(GTK_ENTRY (current_sess->gui->topic_entry)->text);
	topic = strrchr (topic, '@');
	if (topic)
		host = topic + 1;

	auto_insert (buf, sizeof (buf), cmd, 0, 0, "", "", "",
					 server_get_network (current_sess->server, TRUE), host, "",
					 current_sess->channel, "");

	handle_command (current_sess, buf, TRUE);


	SPELL_ENTRY_SET_EDITABLE (current_sess->gui->input_box, FALSE);
	gtk_widget_grab_focus (current_sess->gui->input_box);
	SPELL_ENTRY_SET_EDITABLE (current_sess->gui->input_box, TRUE);
}
