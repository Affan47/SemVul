label_toggled (GtkWidget         *widget,
	       GladeButtonEditor *button_editor)
{
	GladeProperty     *property;
	GValue             value = { 0, };
	gboolean           use_appearance = FALSE;

	if (button_editor->loading || !button_editor->loaded_widget)
		return;

	if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button_editor->label_radio)))
		return;

	button_editor->modifying = TRUE;

	glade_command_push_group (_("Setting %s to use a label and image"), button_editor->loaded_widget->name);

	property = glade_widget_get_property (button_editor->loaded_widget, "stock");
	glade_command_set_property (property, NULL);

	property = glade_widget_get_property (button_editor->loaded_widget, "use-stock");
	glade_command_set_property (property, FALSE);

	glade_widget_property_get (button_editor->loaded_widget, "use-action-appearance", &use_appearance);
	if (!use_appearance)
	{
		property = glade_widget_get_property (button_editor->loaded_widget, "label");
		glade_property_get_default (property, &value);
		glade_command_set_property_value (property, &value);
		g_value_unset (&value);
	}

	glade_command_pop_group ();

	button_editor->modifying = FALSE;


	glade_editable_load (GLADE_EDITABLE (button_editor),
			     button_editor->loaded_widget);
}
