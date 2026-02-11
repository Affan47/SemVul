write(std::ostream& os) const
    {

        std::string::size_type pos = value_.find_last_not_of('\0');
        return os << value_.substr(0, pos + 1);
    }
