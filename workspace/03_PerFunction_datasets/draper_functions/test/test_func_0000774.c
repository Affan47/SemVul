ssl_write(SSL *ssl, const uint8_t *out_data, int out_len)
{
    int n = out_len, nw, i, tot = 0;


    do
    {
        nw = n;

        if (nw > RT_MAX_PLAIN_LENGTH)
            nw = RT_MAX_PLAIN_LENGTH;

        if ((i = send_packet(ssl, PT_APP_PROTOCOL_DATA,
                                            &out_data[tot], nw)) <= 0)
        {
            out_len = i;
            break;
        }

        tot += i;
        n -= i;
    } while (n > 0);

    return out_len;
}
