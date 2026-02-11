yajl_gen_null(yajl_gen g)
{
    ENSURE_VALID_STATE; ENSURE_NOT_KEY; INSERT_SEP; INSERT_WHITESPACE;
    yajl_buf_append(g->buf, "null", strlen("null"));
    APPENDED_ATOM;
    FINAL_NEWLINE;
    return yajl_gen_status_ok;
}
