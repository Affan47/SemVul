find_best_worker(jk_ws_service_t *s,
                            lb_worker_t *p,
                            int *states,
                            jk_logger_t *l)
{
    int rc = -1;

    rc = find_best_byvalue(s, p, states, l);

    if (rc < 0)
        rc = find_failover_worker(s, p, states, l);
    return rc;
}
