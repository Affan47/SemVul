rpc_transport_keepalive_options_set (dict_t *options, int32_t interval,
                                     int32_t time)
{
        int                     ret = -1;

        GF_ASSERT (options);
        GF_ASSERT ((interval > 0) || (time > 0));

        ret = dict_set_int32 (options,
                "transport.socket.keepalive-interval", interval);
        if (ret)
                goto out;

        ret = dict_set_int32 (options,
                "transport.socket.keepalive-time", time);
        if (ret)
                goto out;
out:
        return ret;
}
