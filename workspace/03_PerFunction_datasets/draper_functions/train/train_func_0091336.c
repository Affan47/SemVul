find_button (GeditMessageArea *message_area,
	     gint              response_id)
{
	GList *children, *tmp_list;
	GtkWidget *child = NULL;

	children = gtk_container_get_children (
			GTK_CONTAINER (message_area->priv->action_area));

	for (tmp_list = children; tmp_list; tmp_list = tmp_list->next)
	{
		ResponseData *rd = get_response_data (tmp_list->data, FALSE);

		if (rd && rd->response_id == response_id)
		{
			child = tmp_list->data;
			break;
		}
	}

	g_list_free (children);

	return child;
}
