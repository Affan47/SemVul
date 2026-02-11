agent_transact_unix(LIBSSH2_AGENT *agent, agent_transaction_ctx_t transctx)
{
    unsigned char buf[4];
    int rc;


    if (transctx->state == agent_NB_state_request_created) {
        _libssh2_htonu32(buf, transctx->request_len);
        rc = LIBSSH2_SEND_FD(agent->session, agent->fd, buf, sizeof buf, 0);
        if (rc == -EAGAIN)
            return LIBSSH2_ERROR_EAGAIN;
        else if (rc < 0)
            return _libssh2_error(agent->session, LIBSSH2_ERROR_SOCKET_SEND,
                                  "agent send failed");
        transctx->state = agent_NB_state_request_length_sent;
    }


    if (transctx->state == agent_NB_state_request_length_sent) {
        rc = LIBSSH2_SEND_FD(agent->session, agent->fd, transctx->request,
                           transctx->request_len, 0);
        if (rc == -EAGAIN)
            return LIBSSH2_ERROR_EAGAIN;
        else if (rc < 0)
            return _libssh2_error(agent->session, LIBSSH2_ERROR_SOCKET_SEND,
                                  "agent send failed");
        transctx->state = agent_NB_state_request_sent;
    }


    if (transctx->state == agent_NB_state_request_sent) {
        rc = LIBSSH2_RECV_FD(agent->session, agent->fd, buf, sizeof buf, 0);
        if (rc < 0) {
            if (rc == -EAGAIN)
                return LIBSSH2_ERROR_EAGAIN;
            return _libssh2_error(agent->session, LIBSSH2_ERROR_SOCKET_RECV,
                                  "agent recv failed");
        }
        transctx->response_len = _libssh2_ntohu32(buf);
        transctx->response = LIBSSH2_ALLOC(agent->session,
                                           transctx->response_len);
        if (!transctx->response)
            return LIBSSH2_ERROR_ALLOC;

        transctx->state = agent_NB_state_response_length_received;
    }


    if (transctx->state == agent_NB_state_response_length_received) {
        rc = LIBSSH2_RECV_FD(agent->session, agent->fd, transctx->response,
                           transctx->response_len, 0);
        if (rc < 0) {
            if (rc == -EAGAIN)
                return LIBSSH2_ERROR_EAGAIN;
            return _libssh2_error(agent->session, LIBSSH2_ERROR_SOCKET_SEND,
                                  "agent recv failed");
        }
        transctx->state = agent_NB_state_response_received;
    }

    return 0;
}
