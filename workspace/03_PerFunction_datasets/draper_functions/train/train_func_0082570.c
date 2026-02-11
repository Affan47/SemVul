nspr_filter_setsocketOption(PRFileDesc *fd, const PRSocketOptionData *data) {
    nss_filter_ctx_t *filter_ctx = (nss_filter_ctx_t *)(fd->secret);
    conn_rec *c = filter_ctx->c;
    SSLConnRec *sslconn = myConnConfig(c);
    PRStatus rv = PR_FAILURE;

    switch(data->option) {
        case PR_SockOpt_Nonblocking:
            if (apr_socket_opt_set(sslconn->client_socket, APR_SO_NONBLOCK, data->value.non_blocking) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_Linger:
            if (apr_socket_opt_set(sslconn->client_socket, APR_SO_LINGER, data->value.linger.polarity) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_NoDelay:
            if (apr_socket_opt_set(sslconn->client_socket, APR_TCP_NODELAY, data->value.no_delay) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
        case PR_SockOpt_Reuseaddr:
            if (apr_socket_opt_set(sslconn->client_socket, APR_SO_REUSEADDR, data->value.reuse_addr) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_Keepalive:
            if (apr_socket_opt_set(sslconn->client_socket, APR_SO_KEEPALIVE, data->value.keep_alive) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_RecvBufferSize:
            if (apr_socket_opt_set(sslconn->client_socket, APR_SO_RCVBUF, data->value.recv_buffer_size) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
            break;
        case PR_SockOpt_SendBufferSize:
            if (apr_socket_opt_set(sslconn->client_socket, APR_SO_SNDBUF, data->value.send_buffer_size) == APR_SUCCESS) {
                rv = PR_SUCCESS;
            }
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
