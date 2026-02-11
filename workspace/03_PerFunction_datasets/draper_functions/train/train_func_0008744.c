libssh2_channel_receive_window_adjust2(LIBSSH2_CHANNEL *channel,
                                       unsigned long adj,
                                       unsigned char force,
                                       unsigned int *window)
{
    int rc;

    if(!channel)
        return LIBSSH2_ERROR_BAD_USE;

    BLOCK_ADJUST(rc, channel->session,
                 _libssh2_channel_receive_window_adjust(channel, adj, force,
                                                        window));
    return rc;
}
