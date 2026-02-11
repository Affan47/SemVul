udpc_destroy(Udpc *udpc)
{
    if (udpc == NULL)
        return;

    if (udpc->fd >= 0)
        close(udpc->fd);
    octstr_destroy(udpc->addr);
    gw_assert(gwlist_len(udpc->outgoing_list) == 0);
    gwlist_destroy(udpc->outgoing_list, NULL);

    gw_free(udpc);
}
