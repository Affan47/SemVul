send_bind (own_t *destination_, reader_t *in_pipe_,
    writer_t *out_pipe_, const blob_t &peer_identity_, bool inc_seqnum_)
{
    if (inc_seqnum_)
        destination_->inc_seqnum ();

    command_t cmd;
#if defined ZMQ_MAKE_VALGRIND_HAPPY
    memset (&cmd, 0, sizeof (cmd));
#endif
    cmd.destination = destination_;
    cmd.type = command_t::bind;
    cmd.args.bind.in_pipe = in_pipe_;
    cmd.args.bind.out_pipe = out_pipe_;
    if (peer_identity_.empty ()) {
        cmd.args.bind.peer_identity_size = 0;
        cmd.args.bind.peer_identity = NULL;
    }
    else {
        zmq_assert (peer_identity_.size () <= 0xff);
        cmd.args.bind.peer_identity_size =
            (unsigned char) peer_identity_.size ();
        cmd.args.bind.peer_identity =
            (unsigned char*) malloc (peer_identity_.size ());
        alloc_assert (cmd.args.bind.peer_identity_size);
        memcpy (cmd.args.bind.peer_identity, peer_identity_.data (),
            peer_identity_.size ());
    }
    send_command (cmd);
}
