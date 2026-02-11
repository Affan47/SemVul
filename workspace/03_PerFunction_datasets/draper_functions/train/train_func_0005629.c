item_type_changed(GtkComboBox *item_type_combo,
				ToolbarPage *prefs_toolbar)
{
	gint active = gtk_combo_box_get_active(item_type_combo);

	switch(active) {
	case ITEM_FUNCTION:
		gtk_widget_show(prefs_toolbar->item_func_combo);
		gtk_widget_hide(prefs_toolbar->item_action_combo);
		gtk_widget_hide(prefs_toolbar->item_plugin_combo);
		gtk_combo_box_set_active(
			GTK_COMBO_BOX(prefs_toolbar->item_func_combo), 0);
		gtk_button_set_label(GTK_BUTTON(prefs_toolbar->icon_button), "");
		gtk_widget_set_sensitive(prefs_toolbar->item_text_entry, TRUE);
		gtk_widget_set_sensitive(prefs_toolbar->item_func_combo, TRUE);
		gtk_widget_set_sensitive(prefs_toolbar->icon_button, TRUE);

		func_selection_changed(GTK_COMBO_BOX(prefs_toolbar->item_func_combo),
					prefs_toolbar);
		break;
	case ITEM_USER_ACTION:
		gtk_widget_show(prefs_toolbar->item_action_combo);
		gtk_widget_hide(prefs_toolbar->item_func_combo);
		gtk_widget_hide(prefs_toolbar->item_plugin_combo);
		gtk_combo_box_set_active(
			GTK_COMBO_BOX(prefs_toolbar->item_action_combo), 0);
		gtk_button_set_label(GTK_BUTTON(prefs_toolbar->icon_button), "");
		gtk_widget_set_sensitive(prefs_toolbar->item_text_entry, FALSE);
		gtk_widget_set_sensitive(prefs_toolbar->item_action_combo, TRUE);
		gtk_widget_set_sensitive(prefs_toolbar->icon_button, TRUE);

		action_selection_changed(GTK_COMBO_BOX(prefs_toolbar->item_action_combo),
					prefs_toolbar);
		break;
	case ITEM_SEPARATOR:
		gtk_button_set_label(GTK_BUTTON(prefs_toolbar->icon_button), _("None"));
		gtk_button_set_image(GTK_BUTTON(prefs_toolbar->icon_button), NULL);
		g_free(prefs_toolbar->item_icon_file);
		prefs_toolbar->item_icon_file = NULL;
		gtk_combo_box_set_active(
			GTK_COMBO_BOX(prefs_toolbar->item_func_combo), -1);
		gtk_combo_box_set_active(
			GTK_COMBO_BOX(prefs_toolbar->item_action_combo), -1);
		gtk_combo_box_set_active(
			GTK_COMBO_BOX(prefs_toolbar->item_plugin_combo), -1);
		gtk_entry_set_text(GTK_ENTRY(prefs_toolbar->item_text_entry), "");
		gtk_widget_set_sensitive(prefs_toolbar->item_action_combo, FALSE);
		gtk_widget_set_sensitive(prefs_toolbar->item_text_entry, FALSE);
		gtk_widget_set_sensitive(prefs_toolbar->item_plugin_combo, FALSE);
		gtk_widget_set_sensitive(prefs_toolbar->item_func_combo, FALSE);
		gtk_widget_set_sensitive(prefs_toolbar->icon_button, FALSE);
		break;
	  case ITEM_PLUGIN:
	  	gtk_widget_show(prefs_toolbar->item_plugin_combo);
	  	gtk_widget_hide(prefs_toolbar->item_func_combo);
	  	gtk_widget_hide(prefs_toolbar->item_action_combo);
	  	gtk_combo_box_set_active(GTK_COMBO_BOX(prefs_toolbar->item_plugin_combo), 0);
	  	gtk_button_set_label(GTK_BUTTON(prefs_toolbar->icon_button), "");
	  	gtk_widget_set_sensitive(prefs_toolbar->item_text_entry, FALSE);
	  	gtk_widget_set_sensitive(prefs_toolbar->item_plugin_combo, TRUE);
	  	gtk_widget_set_sensitive(prefs_toolbar->icon_button, TRUE);
	  	plugin_selection_changed(GTK_COMBO_BOX(prefs_toolbar->item_plugin_combo), prefs_toolbar);
	  	break;
	}

}
