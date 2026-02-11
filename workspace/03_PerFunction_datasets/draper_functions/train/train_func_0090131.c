set_government_choice(struct government *government)
{
  if (NULL != client.conn.playing
      && can_client_issue_orders()
      && government != government_of_player(client.conn.playing)) {
    dsend_packet_player_change_government(&client.conn, government_number(government));
  }
}
