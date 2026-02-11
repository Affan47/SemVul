fcgi_protocol_queue_client_buffer(fcgi_request *fr)
{
    int movelen;
    int in_len, out_free;

    if (fr->eofSent)
        return;


    in_len = BufferLength(fr->clientInputBuffer);
    out_free = max(0, BufferFree(fr->serverOutputBuffer) - sizeof(FCGI_Header));
    movelen = min(in_len, out_free);
    if (movelen > 0) {
        queue_header(fr, FCGI_STDIN, movelen);
        fcgi_buf_get_to_buf(fr->serverOutputBuffer, fr->clientInputBuffer, movelen);
    }


    if (movelen == in_len && fr->expectingClientContent <= 0
            && BufferFree(fr->serverOutputBuffer) >= sizeof(FCGI_Header))
    {
        queue_header(fr, FCGI_STDIN, 0);
        fr->eofSent = TRUE;
    }
}
