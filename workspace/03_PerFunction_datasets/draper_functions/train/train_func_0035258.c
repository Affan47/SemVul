download_attach_socket(struct download *d, gnutella_socket_t *s)
{
	download_check(d);

	if (d->socket != NULL) {
		g_carp("%s(): download had non-NULL %s socket already (%s)",
			G_STRFUNC, s == d->socket ? "identical" : "distinct",
			download_basename(d));
		if (d->socket != s) {
			socket_detach_ops(d->socket);
			socket_free_null(&d->socket);
		}
	}


	if (s->getline != NULL) {
		getline_free(s->getline);
		s->getline = NULL;
	}

	d->socket = s;
	socket_attach_ops(s, SOCK_TYPE_DOWNLOAD, &download_socket_ops, d);
}
