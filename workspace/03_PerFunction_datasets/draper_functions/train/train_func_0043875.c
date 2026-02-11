vnc_connection_audio_action(VncConnection *conn,
                                        int action)
{
    struct audio_action_data data = {
        conn,
        coroutine_self(),
        action,
    };

    VNC_DEBUG("Emit audio action %d\n", action);

    g_idle_add(do_vnc_connection_audio_action, &data);


    coroutine_yield(NULL);
}
