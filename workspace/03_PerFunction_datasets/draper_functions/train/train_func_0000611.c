process_pipe_term ()
{
    if (endpoint)
        endpoint->detach_outpipe (this);

    reader_t *p = peer;
    peer = NULL;
    send_pipe_term_ack (p);
}
