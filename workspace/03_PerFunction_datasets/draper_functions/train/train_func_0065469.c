summary_filter_get_mode(void)


{


	GtkWidget *vbox;
	GtkWidget *account_rules_skip;
	GtkWidget *account_rules_force;
	GtkWidget *account_rules_user_current;
	AlertValue val;

	vbox = gtk_vbox_new (FALSE, 0);

	account_rules_skip = gtk_radio_button_new_with_label
							(NULL, _("Skip these rules"));
	account_rules_force = gtk_radio_button_new_with_label_from_widget
							(GTK_RADIO_BUTTON(account_rules_skip),
							_("Apply these rules regardless of the account they belong to"));
	account_rules_user_current = gtk_radio_button_new_with_label_from_widget
							(GTK_RADIO_BUTTON(account_rules_skip),
							_("Apply these rules if they apply to the current account"));
	gtk_box_pack_start (GTK_BOX (vbox), account_rules_skip, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), account_rules_force, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), account_rules_user_current, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(account_rules_skip), "toggled",
			G_CALLBACK(account_rules_radio_button_toggled_cb),
			GINT_TO_POINTER(FILTERING_ACCOUNT_RULES_SKIP));
	g_signal_connect(G_OBJECT(account_rules_force), "toggled",
			G_CALLBACK(account_rules_radio_button_toggled_cb),
			GINT_TO_POINTER(FILTERING_ACCOUNT_RULES_FORCE));
	g_signal_connect(G_OBJECT(account_rules_user_current), "toggled",
			G_CALLBACK(account_rules_radio_button_toggled_cb),
			GINT_TO_POINTER(FILTERING_ACCOUNT_RULES_USE_CURRENT));
	switch (prefs_common.apply_per_account_filtering_rules) {
	case FILTERING_ACCOUNT_RULES_SKIP:
		gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(account_rules_skip), TRUE);
		break;
	case FILTERING_ACCOUNT_RULES_FORCE:
		gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(account_rules_force), TRUE);
		break;
	case FILTERING_ACCOUNT_RULES_USE_CURRENT:
		gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(account_rules_user_current), TRUE);
		break;
	}

	val = alertpanel_with_widget(
			_("Filtering"),
			_("There are some filtering rules that belong to an account.\n"
			  "Please choose what to do with these rules:"),
			GTK_STOCK_CANCEL, _("_Filter"), NULL, TRUE, G_ALERTALTERNATE, vbox);

	if ((val & ~G_ALERTDISABLE) != G_ALERTALTERNATE) {
		return FALSE;
	} else if (val & G_ALERTDISABLE)
		prefs_common.ask_apply_per_account_filtering_rules = FALSE;

	return TRUE;
}
