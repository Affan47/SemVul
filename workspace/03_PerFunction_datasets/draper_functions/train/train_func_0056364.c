connected_to(World *world)
{


  gchar *status_text;

  world->connected         = TRUE;
  world->connecting        = FALSE;
  world->connected_time    = time(NULL);
  world->last_command_time = time(NULL);

  if (world->proxy_used.type == PROXY_NONE) {
    status_text = g_strdup_printf(_("Connected to host %s (%s) port %s."),
                                  world->host, world->host_ip, world->port);
  } else {
    status_text = g_strdup_printf(_("Connected to host %s port %s, via proxy %s (%s) port %s."),
                                  world->host, world->port,
                                  world->proxy_used.server, world->host_ip,
                                  world->proxy_used.port);
  }
  if (world->use_tls) {
    gchar *tmp = status_text;
    status_text = g_strconcat(tmp, _(" SSL enabled."), NULL);
    g_free(tmp);
  }
  ansitextview_append_string_with_fgcolor(world->gui, status_text,
                                          globalPrefs.idxInfoMsgColor);
  ansitextview_append_string(world->gui, "\n");
  gtk_label_set_text(world->gui->lblStatus, status_text);
  g_free(status_text);
  adjust_window_title();

  perform_auto_logon(world);
  execute_hook(world, "OnConnect", NULL);
  if (world->log_autostart) {
    gchar *errmsg = NULL;

    stop_log(world);
    if (start_log(world, 0, &errmsg)) {
      ansitextview_append_stringf(world->gui,
                                  _("Logging to file %s.\n"),
                                  world->log_actual_file);
    } else {
      ansitextview_append_string_nl(world->gui, errmsg);
      g_free(errmsg);
    }
  }


  g_source_remove(world->io_watch_id);
  world->io_watch_id = g_io_add_watch_full(world->iochan,
                                           G_PRIORITY_HIGH,
                                           G_IO_IN | G_IO_HUP | G_IO_ERR,
                                           data_ready_cb,
                                           world,
                                           NULL);


  freeaddrinfo(world->addrinfo);
  world->addrinfo = NULL;

  return TRUE;
}
