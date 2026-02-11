glusterd_transport_inet_keepalive_options_build (dict_t **options,
                                                 const char *hostname, int port)
{
        dict_t  *dict = NULL;
        int32_t interval = -1;
        int32_t time     = -1;
        int     ret = 0;

        GF_ASSERT (options);
        GF_ASSERT (hostname);

        if (!port)
                port = GLUSTERD_DEFAULT_PORT;
        ret = rpc_transport_inet_options_build (&dict, hostname, port);
        if (ret)
                goto out;

        glusterd_transport_keepalive_options_get (&interval, &time);

        if ((interval > 0) || (time > 0))
                ret = rpc_transport_keepalive_options_set (dict, interval, time);
        *options = dict;
out:
        gf_log ("glusterd", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
