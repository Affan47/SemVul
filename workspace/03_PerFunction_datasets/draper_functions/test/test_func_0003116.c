gnac_ui_init_unique(void)
{
#ifdef HAVE_LIBUNIQUE

  app = unique_app_new_with_commands("org.gnome.Gnac", NULL,
      "add-files", UNIQUE_CMD_ADD,
      "debug"    , UNIQUE_CMD_DEBUG,
      "verbose"  , UNIQUE_CMD_VERBOSE,
      NULL);
  g_signal_connect(app, "message-received",
      G_CALLBACK(gnac_ui_message_received_cb), NULL);

  if (unique_app_is_running(app)) {
    libgnac_info(_("An instance of Gnac is already running"));

    UniqueResponse response;


    response = unique_app_send_message(app, UNIQUE_ACTIVATE, NULL);


    if (options.debug) {
      response = unique_app_send_message(app, UNIQUE_CMD_DEBUG, NULL);
      if (response != UNIQUE_RESPONSE_OK) {
        libgnac_warning(_("Failed to transmit the debug option"));
      }

    } else if (options.verbose) {
      response = unique_app_send_message(app, UNIQUE_CMD_VERBOSE, NULL);
      if (response != UNIQUE_RESPONSE_OK) {
        libgnac_warning(_("Failed to transmit the verbose option"));
      }
    }


    if (options.filenames) {
      UniqueMessageData *message = unique_message_data_new();
      gchar **uris = gnac_utils_get_filenames_from_cmd_line(options.filenames);
      g_strfreev(options.filenames);
      if (!unique_message_data_set_uris(message, uris)) {
        libgnac_warning(_("Failed to convert some uris"));
      }
      g_strfreev(uris);
      response = unique_app_send_message(app, UNIQUE_CMD_ADD, message);
      unique_message_data_free(message);
      if (response != UNIQUE_RESPONSE_OK) {
        libgnac_warning(_("Failed to transmit filenames"));
      } else {
        libgnac_info(_("Filenames transmitted to the running instance"));
      }
    }

    g_object_unref(app);

    gnac_exit(response == UNIQUE_RESPONSE_OK);
  }
#endif
}
