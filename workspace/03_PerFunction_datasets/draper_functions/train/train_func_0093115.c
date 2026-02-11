xsend (zmq_msg_t *msg_, int flags_)
{


    if (!more_out) {
        zmq_assert (!current_out);


        if (msg_->flags & ZMQ_MSG_MORE) {

            more_out = true;


            blob_t identity ((unsigned char*) zmq_msg_data (msg_),
                zmq_msg_size (msg_));
            outpipes_t::iterator it = outpipes.find (identity);

            if (it != outpipes.end ()) {
                current_out = it->second.writer;
                zmq_msg_t empty;
                int rc = zmq_msg_init (&empty);
                zmq_assert (rc == 0);
                if (!current_out->check_write (&empty)) {
                    it->second.active = false;
                    more_out = false;
                    current_out = NULL;
                }
                rc = zmq_msg_close (&empty);
                zmq_assert (rc == 0);
            }
        }

        int rc = zmq_msg_close (msg_);
        zmq_assert (rc == 0);
        rc = zmq_msg_init (msg_);
        zmq_assert (rc == 0);
        return 0;
    }


    more_out = msg_->flags & ZMQ_MSG_MORE;


    if (current_out) {
        bool ok = current_out->write (msg_);
        zmq_assert (ok);
        if (!more_out) {
            current_out->flush ();
            current_out = NULL;
        }
    }
    else {
        int rc = zmq_msg_close (msg_);
        zmq_assert (rc == 0);
    }

    int rc = zmq_msg_init (msg_);
    zmq_assert (rc == 0);

    return 0;
}
