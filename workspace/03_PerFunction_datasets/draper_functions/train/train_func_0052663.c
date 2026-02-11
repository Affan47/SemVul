remove_sockstate_for_domain (gpointer key, gpointer value, gpointer user_data)
{
	MonoMList *list = value;
	gboolean remove = FALSE;
	while (list) {
		MonoObject *data = mono_mlist_get_data (list);
		if (mono_object_domain (data) == user_data) {
			remove = TRUE;
			mono_mlist_set_data (list, NULL);
		}
		list = mono_mlist_next (list);
	}

	return remove;
}
