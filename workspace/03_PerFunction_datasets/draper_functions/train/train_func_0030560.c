skip_indentation(
                boost::string_ref src, std::string::size_type i)
        {
            while (i != src.size() && (src[i] == ' ' || src[i] == '\t')) ++i;
            return i;
        }
