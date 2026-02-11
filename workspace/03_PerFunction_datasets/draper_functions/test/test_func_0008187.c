dispatch_engine ()
{
    if (sent && received) {


        zmq_assert (!engine);
        zmq_assert (ephemeral_engine);


        if (session) {
            send_attach (session, ephemeral_engine, peer_identity, true);
            terminate ();
            return;
        }


        zmq_assert (socket);


        if (peer_identity [0] == 0) {
            session = new (std::nothrow) transient_session_t (io_thread,
                socket, options);
            alloc_assert (session);
            session->inc_seqnum ();
            launch_sibling (session);
            send_attach (session, ephemeral_engine, peer_identity, false);
            terminate ();
            return;
        }


        session = socket->find_session (peer_identity);
        if (session) {
            send_attach (session, ephemeral_engine, peer_identity, false);
            terminate ();
            return;
        }


        session = new (std::nothrow) named_session_t (io_thread, socket,
            options, peer_identity);
        alloc_assert (session);
        session->inc_seqnum ();
        launch_sibling (session);
        send_attach (session, ephemeral_engine, peer_identity, false);
        terminate ();
        return;
    }
}
