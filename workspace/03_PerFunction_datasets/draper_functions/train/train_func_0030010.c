show_worker(jk_ws_service_t *s,
                       status_endpoint_t *p,
                       jk_logger_t *l)
{
    const char *worker;
    const char *sub_worker;
    jk_worker_t *jw = NULL;
    lb_sub_worker_t *wr = NULL;

    JK_TRACE_ENTER(l);
    if (fetch_worker_and_sub_worker(p, "showing", &worker, &sub_worker, l) == JK_FALSE ||
        search_worker(s, p, &jw, worker, l) == JK_FALSE) {
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }
    if (sub_worker && sub_worker[0]) {
        if (search_sub_worker(s, p, jw, worker, &wr, sub_worker,
                             NULL, l) == JK_FALSE) {
            JK_TRACE_EXIT(l);
            return JK_FALSE;
        }
    }
    display_worker(s, p, jw, wr, l);

    JK_TRACE_EXIT(l);
    return JK_TRUE;
}
