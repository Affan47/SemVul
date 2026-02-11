fq (zmq_msg_t *msg_, int flags_)
{

    zmq_msg_close (msg_);


    for (int count = active; count != 0; count--) {
        bool fetched = in_pipes [current]->read (msg_);
        current++;
        if (current >= active)
            current = 0;
        if (fetched)
            return 0;
    }


    zmq_msg_init (msg_);
    errno = EAGAIN;
    return -1;
}
