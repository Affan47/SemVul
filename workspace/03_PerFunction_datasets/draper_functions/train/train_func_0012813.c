toolbar_item_ref(GtkToolItem *item)
{
	g_return_if_fail(item != NULL);

	plugin_items = g_slist_append(plugin_items, item);
	g_signal_connect(item, "destroy", G_CALLBACK(toolbar_item_destroy_cb), NULL);
}
