trim_string(const char * arg)
{
    const int max_string_len = 20;

    std::string result = "";
    if (0 == arg) {
        return result;
    }
    int i;
    for ( i = 0; (i < max_string_len) && ('\0' != *arg) && isprint(*arg); i++, arg++) {
        result += *arg;
    }
    return result;
}
