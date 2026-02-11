GetIP()
    {
        tString ret = machine_.GetIP();
        if ( ret.Len() < 4 )
            ret = "everyone";

        return ret;
    }
