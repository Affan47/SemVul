crm_remote_recv(crm_remote_t * remote, int total_timeout  , int *disconnected)
{
    int ret;
    size_t request_len = 0;
    time_t start = time(NULL);
    char *raw_request = NULL;
    int remaining_timeout = 0;

    if (total_timeout == 0) {
        total_timeout = 10000;
    } else if (total_timeout < 0) {
        total_timeout = 60000;
    }
    *disconnected = 0;

    remaining_timeout = total_timeout;
    while ((remaining_timeout > 0) && !(*disconnected)) {


        crm_trace("waiting to receive remote msg, starting timeout %d, remaining_timeout %d",
                  total_timeout, remaining_timeout);
        ret = crm_remote_ready(remote, remaining_timeout);
        raw_request = NULL;

        if (ret == 0) {
            crm_err("poll timed out (%d ms) while waiting to receive msg", remaining_timeout);
            return FALSE;

        } else if (ret < 0) {
            if (errno != EINTR) {
                crm_debug("poll returned error while waiting for msg, rc: %d, errno: %d", ret,
                          errno);
                *disconnected = 1;
                return FALSE;
            }
            crm_debug("poll EINTR encountered during poll, retrying");

        } else if (remote->tcp_socket) {
            raw_request = crm_recv_plaintext(remote->tcp_socket, 0, &request_len, disconnected);

#ifdef HAVE_GNUTLS_GNUTLS_H
        } else if (remote->tls_session) {
            raw_request = crm_recv_tls(remote->tls_session, 0, &request_len, disconnected);
#endif
        } else {
            crm_err("Unsupported connection type");
        }

        remaining_timeout = remaining_timeout - ((time(NULL) - start) * 1000);

        if (!raw_request) {
            crm_debug("Empty msg received after poll");
            continue;
        }

        if (remote->buffer) {
            int old_len = strlen(remote->buffer);

            crm_trace("Expanding recv buffer from %d to %d", old_len, old_len + request_len);

            remote->buffer = realloc(remote->buffer, old_len + request_len + 1);
            memcpy(remote->buffer + old_len, raw_request, request_len);
            *(remote->buffer + old_len + request_len) = '\0';
            free(raw_request);

        } else {
            remote->buffer = raw_request;
        }

        if (strstr(remote->buffer, REMOTE_MSG_TERMINATOR)) {
            return TRUE;
        }
    }

    return FALSE;
}
