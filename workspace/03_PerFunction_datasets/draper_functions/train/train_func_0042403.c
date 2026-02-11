put_buffer(void)
    {
        if (pbase() != pptr())
        {
            std::vector<std::ostream *>::iterator i = ostreams.begin();
            while (i != ostreams.end())
            {
                (*i)->write(pbase(), pptr() - pbase());
                ++i;
            }
            setp(pbase(), epptr());
        }
    }
