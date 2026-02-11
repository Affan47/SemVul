spice_controller_listener_accept_finish (GObject *listener,
                                         GAsyncResult *result,
                                         GObject **source_object,
                                         GError **error)
{
    g_return_val_if_fail(G_IS_OBJECT(listener), NULL);

#ifdef G_OS_WIN32
    SpiceNamedPipeConnection *np;
    np = spice_named_pipe_listener_accept_finish (SPICE_NAMED_PIPE_LISTENER (listener), result, source_object, error);
    if (np)
        return G_IO_STREAM (np);
#else
    GSocketConnection *socket;
    socket = g_socket_listener_accept_finish (G_SOCKET_LISTENER (listener), result, source_object, error);
    if (socket)
        return G_IO_STREAM (socket);
#endif

    return NULL;
}
