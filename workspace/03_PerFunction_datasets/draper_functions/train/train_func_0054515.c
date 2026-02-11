nspr_filter_getsocketoption(PRFileDesc *fd, PRSocketOptionData *data) {
    nss_filter_ctx_t *filter_ctx = (nss_filter_ctx_t *)(fd->secret);
    conn_rec *c = filter_ctx->c;
    SSLConnRec *sslconn = myConnConfig(c);
    apr_int32_t on;
    PRStatus rv = PR_FAILURE;

    switch(data->option) {
        case PR_SockOpt_Nonblocking:
            if (apr_socket_opt_get(sslconn->client_socket, APR_SO_NONBLOCK, &on) == APR_SUCCESS) {
                data->value.non_blocking = (on == 1) ? PR_TRUE : PR_FALSE;
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_Linger:
            if (apr_socket_opt_get(sslconn->client_socket, APR_SO_LINGER, &on) == APR_SUCCESS) {
                data->value.linger.polarity = (on == 1) ? PR_TRUE : PR_FALSE;
                data->value.linger.linger = APR_MAX_SECS_TO_LINGER;
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_NoDelay:
            if (apr_socket_opt_get(sslconn->client_socket, APR_TCP_NODELAY, &on) == APR_SUCCESS) {
                data->value.no_delay = (on == 1) ? PR_TRUE : PR_FALSE;
                rv = PR_SUCCESS;
            }
        case PR_SockOpt_Reuseaddr:
            if (apr_socket_opt_get(sslconn->client_socket, APR_SO_REUSEADDR, &on) == APR_SUCCESS) {
                data->value.reuse_addr = (on == 1) ? PR_TRUE : PR_FALSE;
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_Keepalive:
            if (apr_socket_opt_get(sslconn->client_socket, APR_SO_KEEPALIVE, &on) == APR_SUCCESS) {
                data->value.keep_alive = (on == 1) ? PR_TRUE : PR_FALSE;
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_RecvBufferSize:
        case PR_SockOpt_SendBufferSize:
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server, "For sendbuffersize and recvbuffersize we can only see if they are on, not the value.");
            break;
        case PR_SockOpt_McastLoopback:
        case PR_SockOpt_MaxSegment:
        case PR_SockOpt_IpTimeToLive:
        case PR_SockOpt_IpTypeOfService:
        case PR_SockOpt_McastTimeToLive:
        case PR_SockOpt_McastInterface:
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server, "Unsupported or socket option.");
            break;
        default:
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server, "Unknown socket option.");
            break;
    }

    return rv;
}
