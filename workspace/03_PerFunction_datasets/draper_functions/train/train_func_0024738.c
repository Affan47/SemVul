terminated (reader_t *pipe_)
{
    zmq_assert (in_pipe == pipe_);
    in_pipe = NULL;
    if (state == terminating)
        unregister_term_ack ();
}
