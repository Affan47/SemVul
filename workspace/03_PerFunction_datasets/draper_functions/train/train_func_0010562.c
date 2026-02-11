get_supported_auth_methods_cb (EBookTestClosure *closure)
{


	if (closure->list) {
		EIterator *iter;
		const gchar *field;

		test_print ("supported auth methods:\n");
		iter = e_list_get_iterator (closure->list);
		while ((field = e_iterator_get (iter))) {
			test_print ("    %s\n", field);
			e_iterator_next (iter);
		}
		test_print ("----------------\n");
	}

	g_object_unref (closure->list);

	g_main_loop_quit ((GMainLoop *) (closure->user_data));
}
