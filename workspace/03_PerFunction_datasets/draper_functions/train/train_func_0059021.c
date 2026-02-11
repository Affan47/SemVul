parse_name_value_pair(char* buf, std::string& name, std::string& value) {
    std::basic_string<char>::size_type i;
    std::string s;

    s = std::string(buf);
    i = s.find("=", 0);
    if ( i < s.npos ) {
        name = s.substr(0, i);
        value = s.substr(i + 1);
        strip_whitespace(name);
        strip_whitespace(value);
        return true;
    }
    return false;
}
