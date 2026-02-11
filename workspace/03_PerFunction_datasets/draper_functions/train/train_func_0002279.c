send_turn_done(void)
{
  log_debug("send_turn_done() turn_done_button_state=%d",
            get_turn_done_button_state());

  if (!get_turn_done_button_state()) {


    if (agents_busy()) {
      waiting_for_end_turn = TRUE;
    }

    return;
  }

  waiting_for_end_turn = FALSE;

  attribute_flush();

  dsend_packet_player_phase_done(&client.conn, game.info.turn);

  update_turn_done_button_state();
}
