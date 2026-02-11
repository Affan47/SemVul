parse_unsigned(const char*& s) {

    static const int base(10);

    errno = 0;

    char* endptr;
    const unsigned long val(strtoul(s, &endptr, base));
    if ((errno == ERANGE && (val == ULONG_MAX || val == 0))
        || (errno != 0 && val == 0) || (endptr == s)) {
        parse_exception("unsigned long",s);
    }

    if (val > std::numeric_limits<unsigned>::max()) {
        parse_exception("unsigned",s);
    }

    s = endptr;

    return static_cast<unsigned>(val);
}
