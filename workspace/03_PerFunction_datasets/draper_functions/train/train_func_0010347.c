ladish_studio_run(void)
{
  bool state;

  ladish_cqueue_run(&g_studio.cmd_queue);
  if (g_quit)
  {
    return;
  }

  if (ladish_environment_consume_change(&g_studio.env_store, ladish_environment_jack_server_started, &state))
  {
    ladish_cqueue_clear(&g_studio.cmd_queue);

    if (state)
    {
      ladish_environment_ignore(&g_studio.env_store, ladish_environment_jack_server_present);

      if (g_studio.jack_graph_proxy != NULL)
      {
        log_error("Ignoring \"JACK started\" notification because it is already known that JACK is currently started.");
        return;
      }


      if (g_studio.dbus_object == NULL)
      {
        ASSERT(g_studio.name == NULL);
        if (!ladish_studio_name_generate(&g_studio.name))
        {
          log_error("studio_name_generate() failed.");
          return;
        }

        g_studio.automatic = true;

        ladish_studio_publish();
      }

      ladish_studio_on_event_jack_started();

      if (g_studio.automatic)
      {
        ladish_notify_simple(
          LADISH_NOTIFY_URGENCY_NORMAL,
          "Automatic studio created",
          "JACK server is started not by ladish daemon and there is no loaded studio, so a new studio is created and marked as started.");
      }
    }
    else
    {


      if (g_studio.jack_graph_proxy == NULL)
      {
        log_error("Ignoring \"JACK stopped\" notification because it is already known that JACK is currently stopped.");
        return;
      }

      if (g_studio.automatic)
      {
        log_info("Unloading automatic studio.");
        ladish_command_unload_studio(NULL, &g_studio.cmd_queue);

        ladish_studio_on_event_jack_stopped();
        return;
      }

      log_error("JACK stopped unexpectedly.");
      log_error("Save your work, then unload and reload the studio.");
      ladish_notify_simple(
        LADISH_NOTIFY_URGENCY_HIGH,
        "Studio crashed",
        "JACK stopped unexpectedly.\n\n"
        "Save your work, then unload and reload the studio.");
      ladish_studio_handle_unexpected_jack_server_stop();
    }
  }

  if (ladish_environment_consume_change(&g_studio.env_store, ladish_environment_jack_server_present, &state))
  {
    if (g_studio.jack_graph_proxy != NULL)
    {
      ladish_cqueue_clear(&g_studio.cmd_queue);


      log_error("JACK disappeared unexpectedly. Maybe it crashed.");
      log_error("Save your work, then unload and reload the studio.");
      ladish_notify_simple(
        LADISH_NOTIFY_URGENCY_HIGH,
        "Studio crashed",
        "JACK disappeared unexpectedly. Maybe it crashed.\n\n"
        "Save your work, then unload and reload the studio.");
      ladish_environment_reset_stealth(&g_studio.env_store, ladish_environment_jack_server_started);

      ladish_studio_iterate_virtual_graphs(NULL, ladish_studio_hide_vgraph_non_virtual);

      ladish_studio_handle_unexpected_jack_server_stop();
    }
  }

  ladish_environment_assert_consumed(&g_studio.env_store);
}
