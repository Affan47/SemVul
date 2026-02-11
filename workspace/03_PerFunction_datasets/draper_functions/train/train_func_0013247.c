file_transform_gui_sync(file_transform_gui_t * gui) {

	int err;

	gui->model->rm_number = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->check_rm_number));
	gui->model->rm_extension = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->check_rm_extension));
	gui->model->us_to_space = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->check_us_to_space));
	gui->model->rm_multi_spaces = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->check_rm_multi_spaces));

	strncpy(gui->model->regexp, gtk_entry_get_text(GTK_ENTRY(gui->entry_regexp)), MAXLEN-1);
	strncpy(gui->model->replacement, gtk_entry_get_text(GTK_ENTRY(gui->entry_replacement)), MAXLEN-1);

	gtk_widget_hide(gui->label_error);

	if ((err = regcomp(&gui->model->compiled, gui->model->regexp, REG_EXTENDED | REG_ICASE))) {

		char msg[MAXLEN];
		char * utf8;

		regerror(err, &gui->model->compiled, msg, MAXLEN);
		utf8 = g_filename_to_utf8(msg, -1, NULL, NULL, NULL);
		gtk_label_set_text(GTK_LABEL(gui->label_error), utf8);
		gtk_widget_show(gui->label_error);
		g_free(utf8);

		regfree(&gui->model->compiled);
		gtk_widget_grab_focus(gui->entry_regexp);

		return err;
	}

	if (gui->model->regexp[0] != '\0' && !regexec(&gui->model->compiled, "", 0, NULL, 0)) {

		gtk_label_set_text(GTK_LABEL(gui->label_error), _("Regexp matches empty string"));
		gtk_widget_show(gui->label_error);
		regfree(&gui->model->compiled);
		gtk_widget_grab_focus(gui->entry_regexp);

		return -1;
	}

	return 0;
}
