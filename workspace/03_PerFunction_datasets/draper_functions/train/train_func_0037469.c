to_utf8() const
{
    if (!size()) {
        return byte_array();
    }

    MiniIconv ic("UTF-8", "UTF-16");
    if (!ic.is_valid()) {
        return byte_array();
    }
    const value_type *me_data = data();
    byte_array str(size());
    char *str_data = &str[0];
    size_t me_len_char = size();
    size_t str_len_left = str.size();
    size_t ir = iconv(ic, (ICONV_CONST char **)&me_data, &me_len_char, &str_data, &str_len_left);
    if ((ir == (size_t)-1) && (errno == E2BIG)) {
        const size_t delta = str_data - &str[0];
        str_len_left += str.size();
        str.resize(str.size() * 2);
        str_data = &str[delta];
        ir = iconv(ic, (ICONV_CONST char **)&me_data, &me_len_char, &str_data, &str_len_left);
        if (ir == (size_t)-1) {
            return byte_array();
        }
    }
    str.resize(str.size() - str_len_left);
    return str;
}
