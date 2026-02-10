yajl_gen_string(yajl_gen g, const unsigned char * str,
                size_t len)
{
    ENSURE_VALID_STATE; INSERT_SEP; INSERT_WHITESPACE;
    yajl_buf_append(g->buf, "\"", 1);
    yajl_string_encode(g->buf, str, len);
    yajl_buf_append(g->buf, "\"", 1);
    APPENDED_ATOM;
    FINAL_NEWLINE;
    return yajl_gen_status_ok;
}
