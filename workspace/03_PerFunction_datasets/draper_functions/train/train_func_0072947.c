joind_ok_cb (GtkWidget *ok, server *serv)
{
	if (!is_server (serv))
	{
		gtk_widget_destroy (gtk_widget_get_toplevel (ok));
		return;
	}


	if (GTK_TOGGLE_BUTTON (serv->gui->joind_radio1)->active)
		goto xit;


	if (GTK_TOGGLE_BUTTON (serv->gui->joind_radio2)->active)
	{
		char *text = GTK_ENTRY (serv->gui->joind_entry)->text;
		if (strlen (text) < 2)
		{
			fe_message (_("Channel name too short, try again."), FE_MSG_ERROR);
			return;
		}
		serv->p_join (serv, text, "");
		goto xit;
	}


	chanlist_opengui (serv, TRUE);

xit:
	prefs.hex_gui_join_dialog = 0;
	if (GTK_TOGGLE_BUTTON (serv->gui->joind_check)->active)
		prefs.hex_gui_join_dialog = 1;

	gtk_widget_destroy (serv->gui->joind_win);
	serv->gui->joind_win = NULL;
}
