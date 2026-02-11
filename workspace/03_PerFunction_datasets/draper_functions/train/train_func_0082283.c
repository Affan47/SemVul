hybrid_get_http_length(const gchar *http_response)
{
    gchar       *pos, *stop;
    gchar       *temp;
    gint         length;
    const gchar *cur = "Content-Length: ";

    g_return_val_if_fail(http_response != NULL, 0);

    if (!(pos = g_strrstr(http_response, cur))) {
        hybrid_debug_error("http", "no Content-length in response header.");
        return 0;
    }

    pos += strlen(cur);

    for (stop = pos; *stop && *stop != '\r'; stop ++);

    temp = g_strndup(pos, stop - pos);
    length = atoi(temp);
    g_free(temp);

    return length;
}
