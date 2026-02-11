connection_walk_request(struct linked_server *server,
                        const struct uo_packet_walk *p) {
    struct connection_walk_state *state = &server->connection->walk;
    struct connection_walk_item *i;
    struct uo_packet_walk walk;

    if (state->queue_size > 0 && server != state->server) {
        log(2, "rejecting walk\n");
        walk_cancel(&server->connection->client.world, server->server, p);
        return;
    }

    if (state->queue_size >= MAX_WALK_QUEUE) {

        log(2, "queue full\n");
        walk_cancel(&server->connection->client.world, server->server,
                    &state->queue[0].packet);
        walk_shift(state);
    }

    state->server = server;
    i = &state->queue[state->queue_size++];
    i->packet = *p;

    log(7, "walk seq_from_client=%u seq_to_server=%u\n", p->seq, state->seq_next);

    walk = *p;
    walk.seq = i->seq = (uint8_t)state->seq_next++;
    uo_client_send(server->connection->client.client, &walk, sizeof(walk));

    if (state->seq_next == 0)
        state->seq_next = 1;
}
