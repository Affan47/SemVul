on_search_paths (GObject *source,
                 GAsyncResult *result,
                 gpointer user_data)
{
	GSimpleAsyncResult *res = G_SIMPLE_ASYNC_RESULT (user_data);
	SearchClosure *closure = g_simple_async_result_get_op_res_gpointer (res);
	SecretService *self = closure->service;
	GError *error = NULL;
	gint want = 1;
	gint count;
	gint i;

	secret_service_search_for_dbus_paths_finish (self, result, &closure->unlocked,
	                                             &closure->locked, &error);
	if (error == NULL) {
		want = 1;
		if (closure->flags & SECRET_SEARCH_ALL)
			want = G_MAXINT;
		count = 0;

		for (i = 0; count < want && closure->unlocked[i] != NULL; i++, count++)
			search_load_item_async (self, res, closure, closure->unlocked[i]);
		for (i = 0; count < want && closure->locked[i] != NULL; i++, count++)
			search_load_item_async (self, res, closure, closure->locked[i]);


		if (closure->loading == 0)
			secret_search_unlock_load_or_complete (res, closure);

	} else {
		g_simple_async_result_take_error (res, error);
		g_simple_async_result_complete (res);
	}

	g_object_unref (res);
}
