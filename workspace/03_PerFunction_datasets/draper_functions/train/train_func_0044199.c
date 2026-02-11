send_raw_packet(SSL *ssl, uint8_t protocol)
{
    uint8_t *rec_buf = ssl->bm_all_data;
    int pkt_size = SSL_RECORD_SIZE+ssl->bm_index;
    int sent = 0;
    int ret = SSL_OK;

    rec_buf[0] = protocol;
    rec_buf[1] = 0x03;
    rec_buf[2] = ssl->version & 0x0f;
    rec_buf[3] = ssl->bm_index >> 8;
    rec_buf[4] = ssl->bm_index & 0xff;

    DISPLAY_BYTES(ssl, "sending %d bytes", ssl->bm_all_data,
                             pkt_size, pkt_size);

    while (sent < pkt_size)
    {
        ret = SOCKET_WRITE(ssl->client_fd,
                        &ssl->bm_all_data[sent], pkt_size-sent);

        if (ret >= 0)
            sent += ret;
        else
        {

#ifdef WIN32
            if (GetLastError() != WSAEWOULDBLOCK)
#else
            if (errno != EAGAIN && errno != EWOULDBLOCK)
#endif
                return SSL_ERROR_CONN_LOST;
        }


        if (sent != pkt_size)
        {
            fd_set wfds;
            FD_ZERO(&wfds);
            FD_SET(ssl->client_fd, &wfds);


            if (select(ssl->client_fd + 1, NULL, &wfds, NULL, NULL) < 0)
                return SSL_ERROR_CONN_LOST;
        }
    }

    SET_SSL_FLAG(SSL_NEED_RECORD);
    ssl->bm_index = 0;

    if (protocol != PT_APP_PROTOCOL_DATA)
    {

        ret = SSL_OK;
    }

    return ret;
}
