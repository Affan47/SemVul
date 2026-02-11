_libssh2_channel_nextid(LIBSSH2_SESSION * session)
{
    uint32_t id = session->next_channel;
    LIBSSH2_CHANNEL *channel;

    channel = _libssh2_list_first(&session->channels);

    while (channel) {
        if (channel->local.id > id) {
            id = channel->local.id;
        }
        channel = _libssh2_list_next(&channel->node);
    }


    session->next_channel = id + 1;
    _libssh2_debug(session, LIBSSH2_TRACE_CONN, "Allocated new channel ID#%lu",
                   id);
    return id;
}
