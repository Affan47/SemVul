terminated (writer_t *pipe_)
{


    if (pipes.index (pipe_) < active)
        active--;
    if (pipes.index (pipe_) < eligible)
        eligible--;
    pipes.erase (pipe_);

    if (unlikely (terminating))
        sink->unregister_term_ack ();
}
