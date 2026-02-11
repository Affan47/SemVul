gsb_form_scheduler_frequency_button_changed ( GtkWidget *combo_box,
						       gpointer null )
{
    gchar *selected_item;

    selected_item = gtk_combo_box_get_active_text ( GTK_COMBO_BOX (combo_box));

    if ( !strcmp ( selected_item,
		   _("Once")))
    {
	gtk_widget_hide (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_LIMIT_DATE));
	gtk_widget_hide (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_FREQUENCY_USER_ENTRY));
	gtk_widget_hide (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_FREQUENCY_USER_BUTTON));
    }
    else
    {
	gtk_widget_show (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_LIMIT_DATE));
	if ( !strcmp ( selected_item,
		       _("Custom")))
	{
	    gtk_widget_show (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_FREQUENCY_USER_ENTRY));
	    gtk_widget_show (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_FREQUENCY_USER_BUTTON));
	}
	else
	{
	    gtk_widget_hide (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_FREQUENCY_USER_ENTRY));
	    gtk_widget_hide (gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_FREQUENCY_USER_BUTTON));
	}
    }
    g_free (selected_item);
    return FALSE;
}
