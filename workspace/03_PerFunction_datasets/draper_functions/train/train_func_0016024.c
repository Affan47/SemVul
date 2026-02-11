xrecv (zmq_msg_t *msg_, int flags_)
{
    while (true) {


        int rc = fq (msg_, flags_);


        if (rc != 0 && errno == EAGAIN)
            return -1;


        if (!all_count && prefixes.empty () && topics.empty ()) {
            errno = EAGAIN;
            return -1;
        }


        if (all_count)
            return 0;


        unsigned char *data = (unsigned char*) zmq_msg_data (msg_);
        zmq_assert (*data <= zmq_msg_size (msg_) - 1);
        std::string topic ((const char*) (data + 1), *data);


        for (subscriptions_t::iterator it = prefixes.begin ();
              it != prefixes.end (); it++)
            if (it->size () <= topic.size () &&
                  *it == topic.substr (0, it->size ()))
                return 0;


        subscriptions_t::iterator it = topics.find (topic);
        if (it != topics.end ())
            return 0;
    }
}
