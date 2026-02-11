indirect_client_lookup (GdmXdmcpDisplayFactory *factory,
                        GdmAddress             *address)
{
        GSList         *li;
        GSList         *qlist;
        IndirectClient *ret;
        time_t          curtime;

        g_assert (address != NULL);

        curtime = time (NULL);
        ret = NULL;

        qlist = g_slist_copy (factory->priv->indirect_clients);

        for (li = qlist; li != NULL; li = li->next) {
                IndirectClient *ic;
                char           *host;
                char           *serv;

                ic = (IndirectClient *) li->data;

                if (ic == NULL) {
                        continue;
                }

                host = NULL;
                serv = NULL;
                gdm_address_get_numeric_info (ic->dsp_address, &host, &serv);

                g_debug ("GdmXdmcpDisplayFactory: comparing %s:%s",
                        host ? host : "(null)", serv ? serv : "(null)");
                if (gdm_address_equal (ic->dsp_address, address)) {
                        ret = ic;
                        g_free (host);
                        g_free (serv);
                        break;
                }

                if (ic->acctime > 0 && curtime > ic->acctime + factory->priv->max_wait_indirect) {
                        g_debug ("GdmXdmcpDisplayFactory: Disposing stale forward query from %s:%s",
                                 host ? host : "(null)", serv ? serv : "(null)");

                        indirect_client_destroy (factory, ic);
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
