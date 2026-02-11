get_replacement_character(const char *encname, size_t *len_ret, const char **repl_encname_ptr)
{
    if (encoding_equal(encname, "UTF-8")) {
        *len_ret = 3;
        *repl_encname_ptr = "UTF-8";
        return "\xEF\xBF\xBD";
    }
    else {
        *len_ret = 1;
        *repl_encname_ptr = "US-ASCII";
        return "?";
    }
}
