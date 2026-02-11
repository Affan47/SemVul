skip_char(InputStream * inp) {
    int ch = read_stream(inp);
    buf_add(ch);
    return ch;
}
