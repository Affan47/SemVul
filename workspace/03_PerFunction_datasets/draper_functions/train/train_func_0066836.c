is_linked(const char *host)
{
    LIST   *list;
    LINK   *link;
    CONNECTION *serv;

    if(!strcasecmp(host, global.serverName))
        return 1;


    for (list = global.serversList; list; list = list->next)
    {
        serv = list->data;
        if(!strcasecmp(serv->host, host))
            return 1;
    }


    for (list = global.serverLinksList; list; list = list->next)
    {
        link = list->data;
        if(!strcasecmp(link->server, host) || !strcasecmp(link->peer, host))
            return 1;
    }
    return 0;
}
