camel_session_get_socks_proxy (CamelSession *session,
                               const gchar *for_host,
                               gchar **host_ret,
                               gint *port_ret)
{
	CamelSessionClass *class;

	g_return_if_fail (CAMEL_IS_SESSION (session));
	g_return_if_fail (for_host != NULL);
	g_return_if_fail (host_ret != NULL);
	g_return_if_fail (port_ret != NULL);

	class = CAMEL_SESSION_GET_CLASS (session);
	g_return_if_fail (class->get_socks_proxy != NULL);

	class->get_socks_proxy (session, for_host, host_ret, port_ret);
}
