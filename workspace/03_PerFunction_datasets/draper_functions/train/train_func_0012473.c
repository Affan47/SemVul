tools_read_string_size(generic_file & f, string & s, infinint taille)
    {
        U_16 small_read = 0;
        U_I max_read = 0;
        S_I lu = 0;
        const U_I buf_size = 10240;
        char buffer[buf_size];

        s = "";
        do
        {
            if(small_read > 0)
            {
                max_read = small_read > buf_size ? buf_size : small_read;
                lu = f.read(buffer, max_read);
                small_read -= lu;
                s += string((char *)buffer, (char *)buffer+lu);
            }
            taille.unstack(small_read);
        }
        while(small_read > 0);
    }
