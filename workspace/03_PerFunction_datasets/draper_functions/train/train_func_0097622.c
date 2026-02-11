set_turn_to_next_player_and_notify_him(connection_data *connection, int player_id) {
    int index, loop_hole = 0;

    for (index = player_id + 1; index != player_id; index++) {
        if (loop_hole)
            return;
        if (index == MAX_CONNECTIONS) {
            index = 0;
            if (player_id == -1)
                loop_hole = 1;
        }
        if (connection->players[index].fd && !(connection->players[index].view_only)) {

            log_debug("moving the turn from %d to %d", player_id, index);
            connection->last_player_played = player_id;
            connection->current_player_turn = index;
            notify_player_for_its_turn(connection);
            return;
        }
    }
    log_debug("no suitable players found");
}
