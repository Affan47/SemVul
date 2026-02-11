process_term (int linger_)
{

    zmq_assert (!terminating);


    for (owned_t::iterator it = owned.begin (); it != owned.end (); ++it)
        send_term (*it, linger_);
    register_term_acks (owned.size ());
    owned.clear ();


    terminating = true;
    check_term_acks ();
}
