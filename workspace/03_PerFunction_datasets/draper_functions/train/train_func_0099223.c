forward_query_lookup (GdmXdmcpDisplayFactory *factory,
                          GdmAddress             *address)
{
        GSList       *li;
        GSList       *qlist;
        ForwardQuery *ret;
        time_t        curtime;

        curtime = time (NULL);
        ret = NULL;

        qlist = g_slist_copy (factory->priv->forward_queries);

        for (li = qlist; li != NULL; li = li->next) {
                ForwardQuery *q;
                char         *host;
                char         *serv;

                q = (ForwardQuery *) li->data;

                if (q == NULL) {
                        continue;
                }

                host = NULL;
                serv = NULL;
                gdm_address_get_numeric_info (q->dsp_address, &host, &serv);

                g_debug ("GdmXdmcpDisplayFactory: comparing %s:%s",
                        host ? host : "(null)", serv ? serv : "(null)");
                if (gdm_address_equal (q->dsp_address, address)) {
                        ret = q;
                        g_free (host);
                        g_free (serv);
                        break;
                }

                if (q->acctime > 0 &&  curtime > q->acctime + GDM_FORWARD_QUERY_TIMEOUT) {
                        g_debug ("GdmXdmcpDisplayFactory: Disposing stale forward query from %s:%s",
                                 host ? host : "(null)", serv ? serv : "(null)");

                        forward_query_destroy (factory, q);
                }

                g_free (host);
                g_free (serv);
        }

        g_slist_free (qlist);

        if (ret == NULL) {
                char *host;

                host = NULL;
                gdm_address_get_numeric_info (address, &host, NULL);
                g_debug ("GdmXdmcpDisplayFactory: Host %s not found",
                         host ? host : "(null)");
                g_free (host);
        }

        return ret;
}
