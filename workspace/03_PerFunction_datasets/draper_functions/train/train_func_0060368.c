auto_separator_update(GeanyAutoSeparator *autosep)
{
	g_return_if_fail(autosep->item_count >= 0);

	if (autosep->widget)
	{
		if (autosep->item_count > 0)
			ui_widget_show_hide(autosep->widget, autosep->show_count > 0);
		else
			gtk_widget_destroy(autosep->widget);
	}
}
