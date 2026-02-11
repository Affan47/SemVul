xrecv (zmq_msg_t *msg_, int flags_)
{

    if (!receiving_reply) {
        errno = EFSM;
        return -1;
    }


    if (message_begins) {
        int rc = xreq_t::xrecv (msg_, flags_);
        if (rc != 0)
            return rc;


        if (!(msg_->flags & ZMQ_MSG_MORE) || zmq_msg_size (msg_) != 0) {
            errno = EAGAIN;
            return -1;
        }
        message_begins = false;
    }

    int rc = xreq_t::xrecv (msg_, flags_);
    if (rc != 0)
        return rc;


    if (!(msg_->flags & ZMQ_MSG_MORE)) {
        receiving_reply = false;
        message_begins = true;
    }

    return 0;
}
