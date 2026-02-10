connect_to_socks5_proxy (CamelTcpStreamRaw *raw,
                         const gchar *proxy_host,
                         gint proxy_port,
                         const gchar *host,
                         const gchar *service,
                         gint fallback_port,
                         GCancellable *cancellable,
                         GError **error)
{
	PRFileDesc *fd;
	gint port;

	fd = connect_to_proxy (
		raw, proxy_host, proxy_port, cancellable, error);
	if (!fd)
		goto error;

	port = resolve_port (service, fallback_port, cancellable, error);
	if (port == 0)
		goto error;

	if (!socks5_initiate_and_request_authentication (raw, fd, cancellable, error))
		goto error;

	if (!socks5_request_connect (raw, fd, host, port, cancellable, error))
		goto error;

	d (g_print ("  success\n"));

	goto out;

error:
	if (fd) {
		gint save_errno;

		save_errno = errno;
		PR_Shutdown (fd, PR_SHUTDOWN_BOTH);
		PR_Close (fd);
		errno = save_errno;
		fd = NULL;
	}

	d (g_print ("  returning errno %d\n", errno));

out:

	d (g_print ("}\n"));

	return fd;

}
