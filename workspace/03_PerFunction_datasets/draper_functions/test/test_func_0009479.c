read_string_with_length(unsigned len, std::string& to)
{
    align();

    to.resize(len);

    ensureBytes(len);
    for (unsigned int i = 0; i < len; ++i)
    {
        to[i] = read_u8();
    }


    std::string::size_type last = to.find_last_not_of('\0');
    if ( last == std::string::npos ) to.clear();
    else {
        ++last;
        if (last < len) {

            to.erase(last);
        }
    }

}
