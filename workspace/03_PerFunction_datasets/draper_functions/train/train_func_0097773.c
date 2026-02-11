sashimi_timeout (sashimiConnection* conn, guint timeout)
{
	g_return_if_fail(conn != NULL);

	g_mutex_lock(conn->mutex);
	conn->timeout = timeout;
	g_mutex_unlock(conn->mutex);
}
