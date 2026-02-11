channel_close_listener(Channel * c) {
    LINK * l = NULL;

    for (l = clients.next; l != &clients;) {
        StreamClient * client = all2client(l);
        l = l->next;
        if (client->channel == c) {
            trace(LOG_ALWAYS, "Stream is left connected by client: VS%d", client->stream->id);
            delete_client(client);
        }
    }

    for (l = subscriptions.next; l != &subscriptions;) {
        Subscription * h = all2subscription(l);
        l = l->next;
        if (h->channel == c) {
            delete_subscription(h);
        }
    }
}
