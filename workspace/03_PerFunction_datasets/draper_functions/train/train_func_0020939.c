dma_thread_find_local (Locals *self, gint thread, guint frame)
{
	GList *list;
	DmaThreadAndFrame comp = {thread, frame};

	list = g_list_find_custom (self->list, (gconstpointer) &comp, on_find_local);

	return list == NULL ? NULL : (DmaThreadLocal *)list->data;
}
