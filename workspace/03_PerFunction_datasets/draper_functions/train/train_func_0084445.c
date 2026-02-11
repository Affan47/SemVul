find( const std::string & str, const std::string & sub, int start, int end  )
    {
        ADJUST_INDICES(start, end, (int) str.size());

        std::string::size_type result = str.find( sub, start );


        if( result == std::string::npos ||
           (result + sub.size() > (std::string::size_type)end) )
        {
            return -1;
        }

        return (int) result;
    }
