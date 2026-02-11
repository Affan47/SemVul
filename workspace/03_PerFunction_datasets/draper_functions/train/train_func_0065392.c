process_bind (owned_t *session_,
    reader_t *in_pipe_, writer_t *out_pipe_)
{
    zmq_assert (in_pipe_);
    attach_inpipe (in_pipe_);
    zmq_assert (out_pipe_);
    attach_outpipe (out_pipe_);
}
