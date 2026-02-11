remove_counter(gpointer user_data)
{
	struct connman_counter *counter = user_data;

	DBG("owner %s path %s", counter->owner, counter->path);

	__connman_rtnl_update_interval_remove(counter->interval);

	__connman_service_counter_unregister(counter->path);

	g_free(counter->owner);
	g_free(counter->path);
	g_free(counter);
}
