destroy(jk_worker_t **pThis, jk_logger_t *l)
{
    int rc;
    JK_TRACE_ENTER(l);
    rc = ajp_destroy(pThis, l, AJP13_PROTO);
    JK_TRACE_EXIT(l);
    return rc;
}
