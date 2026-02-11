close ()
{
    app_thread->remove_socket (this);


    dispatcher_t *dispatcher = get_dispatcher ();

    shutting_down = true;

    while (true) {


        if (io_objects.empty () && !pending_term_acks)
            break;


        for (io_objects_t::iterator it = io_objects.begin ();
              it != io_objects.end (); it++)
            send_term (*it);


        pending_term_acks += io_objects.size ();
        io_objects.clear ();


        while (pending_term_acks)
            app_thread->process_commands (true, false);
    }


    sessions_sync.lock ();
    zmq_assert (sessions.empty ());
    sessions_sync.unlock ();

    delete this;


    dispatcher->destroy_socket ();

    return 0;
}
