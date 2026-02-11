service_append_ordered(DBusMessageIter *iter, void *user_data)
{
	if (service_list != NULL)
		g_sequence_foreach(service_list,
					service_append_added_foreach, iter);
}
