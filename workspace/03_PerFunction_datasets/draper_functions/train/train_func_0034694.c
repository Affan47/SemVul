terminate ()
{


    if (terminating)
        return;


    if (!owner) {
        process_term (options.linger);
        return;
    }


    send_term_req (owner, this);
}
