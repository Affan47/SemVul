cm_tdbus_watch_cleanup(void *data)
{
	struct tdbus_connection *conn;
	struct tdbus_watch *watch;
	conn = data;
	watch = conn->watches;
	while (watch != NULL) {
		while (watch->dwatches != NULL) {
			cm_tdbus_watch_remove(watch->dwatches->watch, data);
		}
		watch = watch->next;
	}
}
