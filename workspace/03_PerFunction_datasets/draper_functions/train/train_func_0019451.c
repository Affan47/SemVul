cd_client_create_profile (CdClient *client,
			  const gchar *id,
			  CdObjectScope scope,
			  GHashTable *properties,
			  GCancellable *cancellable,
			  GAsyncReadyCallback callback,
			  gpointer user_data)
{
	const gchar *filename;
	GDBusConnection *connection;
	GDBusMessage *request = NULL;
	gint fd = -1;
	gint retval;
	GList *list, *l;
	GUnixFDList *fd_list = NULL;
	GVariant *body;
	GVariantBuilder builder;
	GSimpleAsyncResult *res;

	g_return_if_fail (CD_IS_CLIENT (client));
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));
	g_return_if_fail (id != NULL);

	res = g_simple_async_result_new (G_OBJECT (client),
					 callback,
					 user_data,
					 cd_client_create_profile);


	g_variant_builder_init (&builder, G_VARIANT_TYPE_ARRAY);
	if (properties != NULL &&
	    g_hash_table_size (properties) > 0) {
		list = g_hash_table_get_keys (properties);
		for (l = list; l != NULL; l = l->next) {
			g_variant_builder_add (&builder,
					       "{ss}",
					       l->data,
					       g_hash_table_lookup (properties,
								    l->data));
		}
		g_list_free (list);
	} else {

		g_variant_builder_add (&builder,
				       "{ss}",
				       CD_PROFILE_PROPERTY_QUALIFIER,
				       "");
	}


	request = g_dbus_message_new_method_call (COLORD_DBUS_SERVICE,
						  COLORD_DBUS_PATH,
						  COLORD_DBUS_INTERFACE,
						  "CreateProfileWithFd");


	if (properties != NULL) {
		filename = g_hash_table_lookup (properties,
						CD_PROFILE_PROPERTY_FILENAME);
		if (filename != NULL) {
			fd = open (filename, O_RDONLY);
			if (fd < 0) {
				g_simple_async_result_set_error (res,
								 CD_CLIENT_ERROR,
								 CD_CLIENT_ERROR_INTERNAL,
								 "Failed to open %s",
								 filename);
				g_simple_async_result_complete_in_idle (res);
				goto out;
			}


			fd_list = g_unix_fd_list_new ();
			retval = g_unix_fd_list_append (fd_list, fd, NULL);
			g_assert (retval != -1);
			g_dbus_message_set_unix_fd_list (request, fd_list);


			close (fd);
		}
	}


	body = g_variant_new ("(ssha{ss})",
			      id,
			      cd_object_scope_to_string (scope),
			      fd > -1 ? 0 : -1,
			      &builder);
	g_dbus_message_set_body (request, body);


	connection = g_dbus_proxy_get_connection (client->priv->proxy);
	g_dbus_connection_send_message_with_reply (connection,
						   request,
						   G_DBUS_SEND_MESSAGE_FLAGS_NONE,
						   CD_CLIENT_MESSAGE_TIMEOUT,
						   NULL,
						   cancellable,
						   cd_client_create_profile_cb,
						   res);
out:
	if (fd_list != NULL)
		g_object_unref (fd_list);
	if (request != NULL)
		g_object_unref (request);
}
