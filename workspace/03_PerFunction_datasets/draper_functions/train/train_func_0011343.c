add_pending_yp (struct yp_server *server)
{
    ypdata_t *current, *yp;
    unsigned count = 0;

    if (server->pending_mounts == NULL)
        return;
    current = server->mounts;
    server->mounts = server->pending_mounts;
    server->pending_mounts = NULL;
    yp = server->mounts;
    while (1)
    {
        count++;
        if (yp->next == NULL)
            break;
        yp = yp->next;
    }
    yp->next = current;
    DEBUG2 ("%u YP entries added to %s", count, server->url);
}
