put_char(int c)
    {
        std::vector<std::ostream *>::iterator i = ostreams.begin();
        while (i != ostreams.end())
        {
            (**i) << static_cast<char>(c);
            ++i;
        }
    }
