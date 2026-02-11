do_move (struct _CamelSExp *f,
         gint argc,
         struct _CamelSExpResult **argv,
         CamelFilterDriver *driver)
{
	gint i;

	d (fprintf (stderr, "moving message...\n"));

	for (i = 0; i < argc; i++) {
		if (argv[i]->type == CAMEL_SEXP_RES_STRING) {

			gchar *folder = argv[i]->value.string;
			CamelFolder *outbox;
			gint last;

			outbox = open_folder (driver, folder);
			if (!outbox)
				break;

			if (outbox == driver->priv->source)
				break;


			last = (i == argc - 1);

			if (!driver->priv->modified && driver->priv->uid && driver->priv->source && camel_folder_has_summary_capability (driver->priv->source)) {
				GPtrArray *uids;

				uids = g_ptr_array_new ();
				g_ptr_array_add (uids, (gchar *) driver->priv->uid);

				camel_folder_transfer_messages_to_sync (
					driver->priv->source, uids, outbox, last,
					NULL, NULL, &driver->priv->error);
				g_ptr_array_free (uids, TRUE);
			} else {
				if (driver->priv->message == NULL)

					driver->priv->message = camel_folder_get_message_sync (
						driver->priv->source, driver->priv->uid, NULL, &driver->priv->error);

				if (!driver->priv->message)
					continue;


				camel_folder_append_message_sync (
					outbox, driver->priv->message, driver->priv->info,
					NULL, NULL, &driver->priv->error);

				if (driver->priv->error == NULL && last) {
					if (driver->priv->source && driver->priv->uid && camel_folder_has_summary_capability (driver->priv->source))
						camel_folder_set_message_flags (
							driver->priv->source, driver->priv->uid,
							CAMEL_MESSAGE_DELETED |
							CAMEL_MESSAGE_SEEN, ~0);
					else
						camel_message_info_set_flags (
							driver->priv->info,
							CAMEL_MESSAGE_DELETED |
							CAMEL_MESSAGE_SEEN |
							CAMEL_MESSAGE_FOLDER_FLAGGED,
							~0);
				}
			}

			if (driver->priv->error == NULL) {
				driver->priv->moved = TRUE;
				camel_filter_driver_log (
					driver, FILTER_LOG_ACTION,
					"Move to folder %s", folder);
			}
		}
	}


	camel_filter_driver_log (
		driver, FILTER_LOG_ACTION,
		"Stopped processing");
	driver->priv->terminated = TRUE;

	return NULL;
}
