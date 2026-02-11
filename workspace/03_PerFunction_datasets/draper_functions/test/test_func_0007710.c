_send_event_to_client(stats_event_t *event, client_t *client)
{
    int len;
    char buf [200];


    len = snprintf (buf, sizeof (buf), "EVENT %s %s %s\n",
            (event->source != NULL) ? event->source : "global",
            event->name ? event->name : "null",
            event->value ? event->value : "null");
    if (len > 0 && len < (int)sizeof (buf))
    {
        client_send_bytes (client, buf, len);
        if (client->con->error)
            return -1;
    }
    return 0;
}
