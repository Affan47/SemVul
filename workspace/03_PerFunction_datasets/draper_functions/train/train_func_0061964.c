fe_userlist_numbers(window_t *sess) {
	if (sess == window_current || !gtk_private_ui(sess)->is_tab) {
#if 0
		char tbuf[256];
		if (sess->total) {
			snprintf(tbuf, sizeof(tbuf), _("%d ops, %d total"), sess->ops,
				 sess->total);
			tbuf[sizeof(tbuf) - 1] = 0;
			gtk_label_set_text(GTK_LABEL(sess->gui->namelistinfo), tbuf);
		} else {
			gtk_label_set_text(GTK_LABEL(sess->gui->namelistinfo), NULL);
		}

		if (sess->type == SESS_CHANNEL && prefs.gui_tweaks & 1)
			fe_set_title(sess);
#endif
		gtk_label_set_text(GTK_LABEL(gtk_private_ui(sess)->namelistinfo), gtk_session_target(sess->session));
	}
}
