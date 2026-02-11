ReadNetSegment(GConfClient *client)
{
        NetSegment *ns;
        GSList *list, *tlist;

        tlist = list = gconf_client_get_list(client, GCONF_PATH "/scan_net_segment",
                                                 GCONF_VALUE_STRING, NULL);
        pthread_mutex_lock(&mutex);
        while (tlist) {
                ns = new NetSegment;
                netseg = g_slist_append(netseg, ns);
                ns->startip = (char *)tlist->data;
                tlist = g_slist_next(tlist);
                ns->endip = (char *)tlist->data;
                tlist = g_slist_next(tlist);
                ns->description = (char *)tlist->data;
                tlist = g_slist_next(tlist);
        }
        pthread_mutex_unlock(&mutex);
        g_slist_free(list);
}
