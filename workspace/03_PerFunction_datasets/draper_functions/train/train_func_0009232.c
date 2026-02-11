e_book_backend_ldap_reconnect (EBookBackendLDAP *bl,
                               EDataBookView *book_view,
                               gint ldap_status)
{
	GTimeVal start, end;
	gulong diff;

	if (enable_debug) {
		printf ("e_book_backend_ldap_reconnect ... \n");
		g_get_current_time (&start);
	}

	g_rec_mutex_lock (&eds_ldap_handler_lock);
	if (!bl->priv->ldap) {
		g_rec_mutex_unlock (&eds_ldap_handler_lock);
		if (enable_debug)
			printf ("e_book_backend_ldap_reconnect ... ldap handler is NULL\n");
		return FALSE;
	}
	g_rec_mutex_unlock (&eds_ldap_handler_lock);


	if (bl->priv->connected && ldap_status == LDAP_SERVER_DOWN) {
		gint ldap_error = LDAP_SUCCESS;

		book_view_notify_status (bl, book_view, _("Reconnecting to LDAP server..."));

		if (!e_book_backend_ldap_connect (bl, NULL)) {
			book_view_notify_status (bl, book_view, "");
			if (enable_debug)
				printf ("e_book_backend_ldap_reconnect ... failed (server down?)\n");
			return FALSE;
		}

		if (bl->priv->auth_dn) {
			g_rec_mutex_lock (&eds_ldap_handler_lock);
			ldap_error = ldap_simple_bind_s (
				bl->priv->ldap,
				bl->priv->auth_dn,
				bl->priv->auth_secret);
			g_rec_mutex_unlock (&eds_ldap_handler_lock);
		}
		book_view_notify_status (bl, book_view, "");

		if (enable_debug) {
			printf ("e_book_backend_ldap_reconnect ... returning %d\n", ldap_error);
			g_get_current_time (&end);
			diff = end.tv_sec * 1000 + end.tv_usec / 1000;
			diff -= start.tv_sec * 1000 + start.tv_usec / 1000;
			printf (
				"e_book_backend_ldap_reconnect took %ld.%03ld seconds\n",
				diff / 1000,diff % 1000);
		}

		return (ldap_error == LDAP_SUCCESS);
	}
	else {
		return FALSE;
	}
}
