distribute (zmq_msg_t *msg_, bool flush_)
{
    int pipes_count = out_pipes.size ();


    if (pipes_count == 0) {
        int rc = zmq_msg_close (msg_);
        zmq_assert (rc == 0);
        rc = zmq_msg_init (msg_);
        zmq_assert (rc == 0);
        return true;
    }


    for (out_pipes_t::iterator it = out_pipes.begin (); it != out_pipes.end ();
          it++)
        if (!(*it)->check_write (zmq_msg_size (msg_)))
            return false;

    msg_content_t *content = (msg_content_t*) msg_->content;


    if (content == (msg_content_t*) ZMQ_VSM) {
        for (out_pipes_t::iterator it = out_pipes.begin ();
              it != out_pipes.end (); it++) {
            (*it)->write (msg_);
            if (flush_)
                (*it)->flush ();
        }
        int rc = zmq_msg_init (msg_);
        zmq_assert (rc == 0);
        return true;
    }


    if (pipes_count == 1) {
        (*out_pipes.begin ())->write (msg_);
        if (flush_)
            (*out_pipes.begin ())->flush ();
        int rc = zmq_msg_init (msg_);
        zmq_assert (rc == 0);
        return true;
    }


    if (msg_->shared)
        content->refcnt.add (pipes_count - 1);
    else {
        content->refcnt.set (pipes_count);
        msg_->shared = true;
    }


    for (out_pipes_t::iterator it = out_pipes.begin (); it != out_pipes.end ();
          it++) {
        (*it)->write (msg_);
        if (flush_)
            (*it)->flush ();
    }


    int rc = zmq_msg_init (msg_);
    zmq_assert (rc == 0);

    return true;
}
