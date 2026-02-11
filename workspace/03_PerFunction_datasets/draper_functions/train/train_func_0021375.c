rules_response_cb (GtkDialog *dialog, int response, gpointer user_data)
{
	VgDefaultView *view = user_data;

	if (response == GTK_RESPONSE_OK)
		vg_rule_list_save ((VgRuleList *) view->rule_list);

	gtk_widget_hide ((GtkWidget *) dialog);
}
