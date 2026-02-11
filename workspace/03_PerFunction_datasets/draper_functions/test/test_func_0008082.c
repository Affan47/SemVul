terminated (writer_t *pipe_)
{
    zmq_assert (pipe_ == outpipe);
    outpipe = NULL;
    outpipe_alive = false;

    if (terminating)
        unregister_term_ack ();
}
