relay_has_changed (relay_server *new, relay_server *old)
{
    do
    {
        if (strcmp (new->mount, old->mount) != 0)
            break;
        if (strcmp (new->server, old->server) != 0)
            break;
        if (new->port != old->port)
            break;
        if (new->mp3metadata != old->mp3metadata)
            break;
        if (new->on_demand != old->on_demand)
            old->on_demand = new->on_demand;
        return 0;
    } while (0);
    return 1;
}
