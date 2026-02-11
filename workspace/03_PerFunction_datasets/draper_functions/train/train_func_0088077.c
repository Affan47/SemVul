glade_tool_button_editor_load (GladeEditable *editable,
			       GladeWidget   *widget)
{
	GladeToolButtonEditor     *button_editor = GLADE_TOOL_BUTTON_EDITOR (editable);
	gboolean                   custom_label  = FALSE, use_appearance = FALSE;
	GladeToolButtonImageMode   image_mode    = 0;
	GList                     *l;

	button_editor->loading = TRUE;


	if (button_editor->loaded_widget)
	{
		g_signal_handlers_disconnect_by_func (G_OBJECT (button_editor->loaded_widget->project),
						      G_CALLBACK (project_changed), button_editor);


		g_object_weak_unref (G_OBJECT (button_editor->loaded_widget->project),
				     (GWeakNotify)project_finalized,
				     button_editor);
	}


	button_editor->loaded_widget = widget;

	if (button_editor->loaded_widget)
	{

		g_signal_connect (G_OBJECT (button_editor->loaded_widget->project), "changed",
				  G_CALLBACK (project_changed), button_editor);


		g_object_weak_ref (G_OBJECT (button_editor->loaded_widget->project),
				   (GWeakNotify)project_finalized,
				   button_editor);
	}


	if (button_editor->embed)
		glade_editable_load (GLADE_EDITABLE (button_editor->embed), widget);

	for (l = button_editor->properties; l; l = l->next)
		glade_editor_property_load_by_widget (GLADE_EDITOR_PROPERTY (l->data), widget);

	if (widget)
	{
		glade_widget_property_get (widget, "image-mode", &image_mode);
		glade_widget_property_get (widget, "custom-label", &custom_label);
		glade_widget_property_get (widget, "use-action-appearance", &use_appearance);

		if (custom_label)
			gtk_toggle_button_set_active
				(GTK_TOGGLE_BUTTON (button_editor->custom_label_radio), TRUE);
		else
			gtk_toggle_button_set_active
				(GTK_TOGGLE_BUTTON (button_editor->standard_label_radio), TRUE);

		switch (image_mode)
		{
		case GLADE_TB_MODE_STOCK:
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button_editor->stock_radio), TRUE);
			break;
		case GLADE_TB_MODE_ICON:
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button_editor->icon_radio), TRUE);
			break;
		case GLADE_TB_MODE_FILENAME:
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button_editor->file_radio), TRUE);
			break;
		case GLADE_TB_MODE_CUSTOM:
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button_editor->custom_radio), TRUE);
			break;
		default:
			break;
		}

		if (use_appearance)
		{
			gtk_widget_set_sensitive (button_editor->label_table, FALSE);
			gtk_widget_set_sensitive (button_editor->image_table, FALSE);
		}
		else
		{
			gtk_widget_set_sensitive (button_editor->label_table, TRUE);
			gtk_widget_set_sensitive (button_editor->image_table, TRUE);
		}
	}
	button_editor->loading = FALSE;
}
