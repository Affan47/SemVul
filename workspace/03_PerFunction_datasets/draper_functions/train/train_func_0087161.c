rfind( const std::string & str, const std::string & sub, int start, int end )
    {
        ADJUST_INDICES(start, end, (int) str.size());

        std::string::size_type result = str.rfind( sub, end );

        if( result == std::string::npos ||
            result < (std::string::size_type)start  ||
           (result + sub.size() > (std::string::size_type)end))
            return -1;

        return (int)result;
    }
