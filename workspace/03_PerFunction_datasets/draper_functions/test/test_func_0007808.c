none_is_null(char* in) {
    return streq(in, "none") ? NULL : in;
}
