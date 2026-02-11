destroy(jk_worker_t **pThis, jk_logger_t *l)
{
    JK_TRACE_ENTER(l);

    if (pThis && *pThis && (*pThis)->worker_private) {
        status_worker_t *private_data = (*pThis)->worker_private;

        jk_close_pool(&private_data->p);
        free(private_data);

        JK_TRACE_EXIT(l);
        return JK_TRUE;
    }

    JK_LOG_NULL_PARAMS(l);
    JK_TRACE_EXIT(l);
    return JK_FALSE;
}
