fm_list_unref(FmList* list)
{
	if(g_atomic_int_dec_and_test(&list->n_ref))
	{
		g_queue_foreach((GQueue*)list, (GFunc)list->funcs->item_unref, NULL);
		g_queue_clear((GQueue*)list);
		g_slice_free(FmList, list);
	}
}
