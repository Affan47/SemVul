xmms_plugin_shutdown ()
{
#ifdef HAVE_VALGRIND


	VALGRIND_DO_LEAK_CHECK
		;
#endif

	while (xmms_plugin_list) {
		xmms_plugin_t *p = xmms_plugin_list->data;


		if (p->object.ref > 1) {
			XMMS_DBG ("%s's refcount is %i",
			          p->name, p->object.ref);
		}

		xmms_object_unref (p);

		xmms_plugin_list = g_list_delete_link (xmms_plugin_list,
		                                       xmms_plugin_list);
	}
}
