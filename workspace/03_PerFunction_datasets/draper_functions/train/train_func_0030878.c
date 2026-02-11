up_wakeups_finalize (GObject *object)
{
	UpWakeups *wakeups;

	g_return_if_fail (object != NULL);
	g_return_if_fail (UP_IS_WAKEUPS (object));

	wakeups = UP_WAKEUPS (object);
	wakeups->priv = UP_WAKEUPS_GET_PRIVATE (wakeups);


	up_wakeups_timerstats_disable (wakeups);

	g_ptr_array_unref (wakeups->priv->data);

	G_OBJECT_CLASS (up_wakeups_parent_class)->finalize (object);
}
