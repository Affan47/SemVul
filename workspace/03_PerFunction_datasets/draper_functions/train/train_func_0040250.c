fm_list_remove_all(FmList* list, gpointer data)
{

	GList* l = ((GQueue*)list)->head;
	for(;l; l=l->next)
	{
		if(l->data == data)
			list->funcs->item_unref(data);
	}
	g_queue_remove_all((GQueue*)list, data);
}
