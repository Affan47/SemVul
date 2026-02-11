remove_books (ENameSelectorDialog *name_selector_dialog)
{
	EContactStore *contact_store;
	GSList        *clients, *l;

	if (!name_selector_dialog->priv->name_selector_model)
		return;

	contact_store = e_name_selector_model_peek_contact_store (
		name_selector_dialog->priv->name_selector_model);


	clients = e_contact_store_get_clients (contact_store);
	for (l = clients; l; l = g_slist_next (l)) {
		EBookClient *client = l->data;
		e_contact_store_remove_client (contact_store, client);
	}
	g_slist_free (clients);


	if (name_selector_dialog->priv->cancellable != NULL) {
		g_cancellable_cancel (name_selector_dialog->priv->cancellable);
		g_object_unref (name_selector_dialog->priv->cancellable);
		name_selector_dialog->priv->cancellable = NULL;
	}
}
