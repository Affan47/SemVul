json_read_ulong(InputStream * inp) {
    unsigned long res = 0;
    int neg = 0;
    int ch = read_stream(inp);
    if (ch == '-') {
        neg = 1;
        ch = read_stream(inp);
    }
    if (ch < '0' || ch > '9') exception(ERR_JSON_SYNTAX);
    res = ch - '0';
    for (;;) {
        ch = peek_stream(inp);
        if (ch < '0' || ch > '9') break;
        read_stream(inp);
        res = res * 10 + (ch - '0');
    }
    if (neg) return ~res + 1;
    return res;
}
