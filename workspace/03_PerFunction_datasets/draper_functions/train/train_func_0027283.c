read_config(void)
{
	GttErrCode conf_errcode;


	gtt_err_set_code (GTT_NO_ERR);
	gtt_load_config ();


	conf_errcode = gtt_err_get_code();
	if (GTT_NO_ERR != conf_errcode)
	{
		const char *fp;
		char *errmsg, *qmsg;
		fp = gtt_get_config_filepath();
		errmsg = gtt_err_to_string (conf_errcode, fp);
		qmsg = g_strconcat (errmsg,
			_("Shall I setup a new configuration?"),
			NULL);

		GtkWidget *mb;
		mb = gtk_message_dialog_new (NULL,
		         GTK_DIALOG_MODAL,
		         GTK_MESSAGE_ERROR,
		         GTK_BUTTONS_YES_NO,
                 "%s",
		         qmsg);
		g_signal_connect (G_OBJECT(mb), "response",
		         G_CALLBACK (read_config_err_run_or_abort),
		         NULL);
		gtk_widget_show (mb);
		g_free (qmsg);
		g_free (errmsg);
	}
	else
	{
		post_read_config();
	}
}
