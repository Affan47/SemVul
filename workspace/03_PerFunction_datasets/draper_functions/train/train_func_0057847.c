send_server_hello_sequence(SSL *ssl)
{
    int ret;

    if ((ret = send_server_hello(ssl)) == SSL_OK)
    {
#ifndef CONFIG_SSL_SKELETON_MODE

        if (IS_SET_SSL_FLAG(SSL_SESSION_RESUME))
        {
            if ((ret = send_change_cipher_spec(ssl)) == SSL_OK)
            {
                ret = send_finished(ssl);
                ssl->next_state = HS_FINISHED;
            }
        }
        else
#endif
        if ((ret = send_certificate(ssl)) == SSL_OK)
        {
#ifdef CONFIG_SSL_CERT_VERIFICATION

            if (IS_SET_SSL_FLAG(SSL_CLIENT_AUTHENTICATION))
            {
                if ((ret = send_certificate_request(ssl)) == SSL_OK)
                {
                    ret = send_server_hello_done(ssl);
                    ssl->next_state = HS_CERTIFICATE;
                }
            }
            else
#endif
            {
                ret = send_server_hello_done(ssl);
                ssl->next_state = HS_CLIENT_KEY_XCHG;
            }
        }
    }

    return ret;
}
