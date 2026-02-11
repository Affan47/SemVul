glusterd_transport_keepalive_options_get (int *interval, int *time)
{
        int     ret = 0;
        xlator_t *this = NULL;

        this = THIS;
        GF_ASSERT (this);

        ret = dict_get_int32 (this->options,
                              "transport.socket.keepalive-interval",
                              interval);
        ret = dict_get_int32 (this->options,
                              "transport.socket.keepalive-time",
                              time);
        return 0;
}
