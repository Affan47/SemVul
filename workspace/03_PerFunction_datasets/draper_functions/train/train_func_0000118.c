init(jk_worker_t *pThis,
                          jk_map_t *props,
                          jk_worker_env_t *we, jk_logger_t *l)
{
    ajp_worker_t *aw;
    ajp_endpoint_t *ae;
    jk_endpoint_t *je;
    int rc;

    JK_TRACE_EXIT(l);

    if (ajp_init(pThis, props, we, l, AJP14_PROTO) == JK_FALSE) {
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }
    aw = pThis->worker_private;


    aw->login->secret_key = jk_get_worker_secret_key(props, aw->name);

    if (aw->login->secret_key == NULL) {
        jk_log(l, JK_LOG_ERROR, "can't malloc secret_key");
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }


    aw->login->web_server_name = strdup(we->server_name);

    if (aw->login->web_server_name == NULL) {
        jk_log(l, JK_LOG_ERROR, "can't malloc web_server_name");
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }

    if (get_endpoint(pThis, &je, l) == JK_FALSE) {
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }
    ae = je->endpoint_private;

    if (ajp_connect_to_endpoint(ae, l) == JK_TRUE) {


        rc = discovery(ae, we, l);
        ajp_close_endpoint(ae, l);
        JK_TRACE_EXIT(l);
        return rc;
    }

    JK_TRACE_EXIT(l);
    return JK_TRUE;
}
