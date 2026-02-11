reconnect ()
{
    if (state == engine_connected || state == engine_connecting) {


        poller->rm_fd (handle);


        socket.close ();


        read_pos = read_size;
        write_pos = write_size;
    }


    if (state == engine_connecting) {
        poller->add_timer (this);
        state = engine_waiting_for_reconnect;
        return;
    }


    socket.reopen ();
    if (socket.get_fd () == retired_fd) {
        poller->add_timer (this);
        state = engine_waiting_for_reconnect;
        return;
    }


    handle = poller->add_fd (socket.get_fd (), this);
    poller->set_pollout (handle);

    state = engine_connecting;
}
