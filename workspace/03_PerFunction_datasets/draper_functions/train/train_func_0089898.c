send_ogg_headers (client_t *client, refbuf_t *headers)
{
    struct ogg_client *client_data = client->format_data;
    refbuf_t *refbuf;
    int written = 0;

    if (client_data->headers_sent)
    {
        client_data->header_page = headers;
        client_data->pos = 0;
        client_data->headers_sent = 0;
    }
    refbuf = client_data->header_page;
    while (refbuf)
    {
        char *data = refbuf->data + client_data->pos;
        unsigned len = refbuf->len - client_data->pos;
        int ret;

        ret = client_send_bytes (client, data, len);
        if (ret > 0)
           written += ret;
        if (ret < (int)len)
            return written ? written : -1;
        client_data->pos += ret;
        if (client_data->pos == refbuf->len)
        {
            refbuf = refbuf->next;
            client_data->header_page = refbuf;
            client_data->pos = 0;
        }
    }
    client_data->headers_sent = 1;
    client_data->headers = headers;
    return written;
}
