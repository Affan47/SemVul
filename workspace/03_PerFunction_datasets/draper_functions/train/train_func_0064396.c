yp_remove (const char *mount)
{
    struct yp_server *server = (struct yp_server *)active_yps;

    thread_rwlock_rlock (&yp_lock);
    while (server)
    {
        ypdata_t *list = server->mounts;

        while (1)
        {
            ypdata_t *yp = find_yp_mount (list, mount);
            if (yp == NULL)
                break;
            if (yp->release || yp->remove)
            {
                list = yp->next;
                continue;
            }
            DEBUG2 ("release %s on YP %s", mount, server->url);
            yp->release = 1;
            yp->next_update = 0;
        }
        server = server->next;
    }
    thread_rwlock_unlock (&yp_lock);
}
