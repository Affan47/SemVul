check_sensitivity (GOActionComboStack *saction, unsigned old_count)
{
	unsigned new_count = gtk_tree_model_iter_n_children (saction->model, NULL);

	if ((old_count > 0) ^ (new_count > 0)) {
		GSList *ptr = gtk_action_get_proxies (GTK_ACTION (saction));
		gboolean is_sensitive = (new_count > 0);
		for ( ; ptr != NULL ; ptr = ptr->next)
			gtk_widget_set_sensitive (ptr->data, is_sensitive);
	}
}
