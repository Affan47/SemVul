iter_get_data (GtkTreeIter *iter)
{
	GList *cur_node = NULL;

	g_return_val_if_fail (iter != NULL, NULL);
	if (iter->user_data == NULL)
		return NULL;
	cur_node = (GList *)iter->user_data;
	if (cur_node == NULL)
		return NULL;
	if (!G_IS_OBJECT (cur_node->data))
		return NULL;

	return G_OBJECT (cur_node->data);
}
