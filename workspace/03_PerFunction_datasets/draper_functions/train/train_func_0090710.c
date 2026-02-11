bogofilter_save_func(PrefsPage *_page)
{
	struct BogofilterPage *page = (struct BogofilterPage *) _page;
	BogofilterConfig *config;

	debug_print("Saving Bogofilter Page\n");

	config = bogofilter_get_config();


	config->process_emails = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->process_emails));


	config->receive_spam = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->receive_spam));


	g_free(config->save_folder);
	config->save_folder = gtk_editable_get_chars(GTK_EDITABLE(page->save_folder), 0, -1);


	config->save_unsure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->save_unsure));


	g_free(config->save_unsure_folder);
	config->save_unsure_folder = gtk_editable_get_chars(GTK_EDITABLE(page->save_unsure_folder), 0, -1);


	config->insert_header = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->insert_header));


	config->whitelist_ab = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->whitelist_ab));
	g_free(config->whitelist_ab_folder);
	config->whitelist_ab_folder = gtk_editable_get_chars(
				GTK_EDITABLE(gtk_bin_get_child(GTK_BIN((page->whitelist_ab_folder_combo)))), 0, -1);

	if (g_utf8_collate(config->whitelist_ab_folder, _("Any")) == 0) {
		g_free(config->whitelist_ab_folder);
		config->whitelist_ab_folder = g_strdup("Any");
	}


	config->learn_from_whitelist = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->learn_from_whitelist_chkbtn));


	g_free(config->bogopath);
	config->bogopath = gtk_editable_get_chars(GTK_EDITABLE(page->bogopath), 0, -1);


	config->max_size = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(page->max_size));


	config->mark_as_read = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->mark_as_read));

	if (config->process_emails) {
		bogofilter_register_hook();
	} else {
		bogofilter_unregister_hook();
	}

	procmsg_register_spam_learner(bogofilter_learn);
	procmsg_spam_set_folder(config->save_folder, bogofilter_get_spam_folder);

	bogofilter_save_config();
}
