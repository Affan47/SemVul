Plugin_RemoveHook(PyObject *plugin, Hook *hook)
{
	GSList *list;

	list = g_slist_find(Plugin_GetHooks(plugin), hook);
	if (list) {

		if (hook->type != HOOK_UNLOAD) {

			BEGIN_XCHAT_CALLS(NONE);
			hexchat_unhook(ph, (hexchat_hook*)hook->data);
			END_XCHAT_CALLS();
		}
		Plugin_SetHooks(plugin,
				g_slist_remove(Plugin_GetHooks(plugin),
					       hook));
		Py_DECREF(hook->callback);
		Py_DECREF(hook->userdata);
		if (hook->name)
			g_free(hook->name);
		g_free(hook);
	}
}
