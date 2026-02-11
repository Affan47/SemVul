rpc_transport_inet_options_build (dict_t **options, const char *hostname,
                                  int port)
{
        dict_t          *dict = NULL;
        char            *host = NULL;
        int             ret = -1;

        GF_ASSERT (options);
        GF_ASSERT (hostname);
        GF_ASSERT (port >= 1024);

        dict = dict_new ();
        if (!dict)
                goto out;

        host = gf_strdup ((char*)hostname);
        if (!hostname) {
                ret = -1;
                goto out;
        }

        ret = dict_set_dynstr (dict, "remote-host", host);
        if (ret) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set remote-host with %s", host);
                goto out;
        }

        ret = dict_set_int32 (dict, "remote-port", port);
        if (ret) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set remote-port with %d", port);
                goto out;
        }
        ret = dict_set_str (dict, "transport.address-family", "inet/inet6");
        if (ret) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set addr-family with inet");
                goto out;
        }

        ret = dict_set_str (dict, "transport-type", "socket");
        if (ret) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to set trans-type with socket");
                goto out;
        }

        *options = dict;
out:
        if (ret) {
                if (host)
                        GF_FREE (host);
                if (dict)
                        dict_unref (dict);
        }

        return ret;
}
