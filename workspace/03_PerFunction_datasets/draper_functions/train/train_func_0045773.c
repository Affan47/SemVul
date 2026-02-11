check_destroy ()
{

    if (destroyed) {


        poller->rm_fd (handle);


        destroy_socket (this);


        send_reaped ();


        own_t::process_destroy ();
    }
}
