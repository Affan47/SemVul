on_button_delete_trigger_clicked(GtkButton *button,
		GmWorldPropertiesDialog *properties) {
	GtkTreeIter iter;
	GmTrigger *trigger;

	trigger = gm_world_properties_dialog_selected_trigger(properties, &iter);

	if (trigger) {
		gm_world_properties_dialog_remove_trigger(properties, &iter);
		gm_trigger_free(trigger);
	} else {
		gm_error_dialog(_("First select a trigger to remove"),
				GTK_WINDOW(properties->dialog));
	}
}
