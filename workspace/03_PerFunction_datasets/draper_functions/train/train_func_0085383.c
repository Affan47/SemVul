ssl_callback_Info(const SSL *ssl, int where, int rc)
{
    conn_rec *c;
    server_rec *s;
    SSLConnRec *scr;


    if ((c = (conn_rec *)SSL_get_app_data((SSL *)ssl)) == NULL) {
        return;
    }

    if ((scr = myConnConfig(c)) == NULL) {
        return;
    }


    if ((where & SSL_CB_ACCEPT_LOOP) && scr->reneg_state == RENEG_REJECT) {
        int state = SSL_get_state((SSL *)ssl);

        if (state == SSL3_ST_SR_CLNT_HELLO_A
            || state == SSL23_ST_SR_CLNT_HELLO_A) {
            scr->reneg_state = RENEG_ABORT;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02042)
                          "rejecting client initiated renegotiation");
        }
    }


    else if ((where & SSL_CB_HANDSHAKE_DONE) && scr->reneg_state == RENEG_INIT) {
        scr->reneg_state = RENEG_REJECT;
    }

    s = mySrvFromConn(c);
    if (s && APLOGdebug(s)) {
        log_tracing_state(ssl, c, s, where, rc);
    }
}
