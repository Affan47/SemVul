handle_server_join_reply(bool you_can_join, const char *message,
                              const char *capability,
                              const char *challenge_file, int conn_id)
{
  const char *s_capability = client.conn.capability;

  sz_strlcpy(client.conn.capability, capability);
  close_connection_dialog();

  if (you_can_join) {
    struct packet_client_info client_info;

    log_verbose("join game accept:%s", message);
    client.conn.established = TRUE;
    client.conn.id = conn_id;

    agents_game_joined();
    set_server_busy(FALSE);

    if (get_client_page() == PAGE_MAIN
        || get_client_page() == PAGE_NETWORK
        || get_client_page() == PAGE_GGZ) {
      set_client_page(PAGE_START);
    }

    client_info.gui = get_gui_type();
    strncpy(client_info.distribution, FREECIV_DISTRIBUTOR,
            sizeof(client_info.distribution));
    send_packet_client_info(&client.conn, &client_info);


    send_client_wants_hack(challenge_file);

    set_client_state(C_S_PREPARING);
  } else {
    output_window_printf(ftc_client,
                         _("You were rejected from the game: %s"), message);
    client.conn.id = -1;

    if (auto_connect) {
      log_normal(_("You were rejected from the game: %s"), message);
    }
    gui_server_connect();

    if (!with_ggz) {
      set_client_page(in_ggz ? PAGE_MAIN : PAGE_GGZ);
    }
  }
  if (strcmp(s_capability, our_capability) == 0) {
    return;
  }
  output_window_printf(ftc_client, _("Client capability string: %s"),
                       our_capability);
  output_window_printf(ftc_client, _("Server capability string: %s"),
                       s_capability);
}
