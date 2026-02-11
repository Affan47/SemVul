plug (io_thread_t *io_thread_, i_inout *inout_)
{
    zmq_assert (!plugged);
    plugged = true;
    ephemeral_inout = NULL;


    zmq_assert (!inout);
    zmq_assert (inout_);
    encoder.set_inout (inout_);
    decoder.set_inout (inout_);
    inout = inout_;


    io_object_t::plug (io_thread_);
    handle = add_fd (tcp_socket.get_fd ());
    set_pollin (handle);
    set_pollout (handle);


    in_event ();
}
