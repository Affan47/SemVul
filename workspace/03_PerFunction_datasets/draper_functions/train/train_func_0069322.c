find_route_worker(proxy_balancer *balancer,
                                       const char *route, request_rec *r)
{
    int i;
    int checking_standby;
    int checked_standby;

    proxy_worker **workers;

    checking_standby = checked_standby = 0;
    while (!checked_standby) {
        workers = (proxy_worker **)balancer->workers->elts;
        for (i = 0; i < balancer->workers->nelts; i++, workers++) {
            proxy_worker *worker = *workers;
            if ( (checking_standby ? !PROXY_WORKER_IS_STANDBY(worker) : PROXY_WORKER_IS_STANDBY(worker)) )
                continue;
            if (*(worker->s->route) && strcmp(worker->s->route, route) == 0) {
                if (PROXY_WORKER_IS_USABLE(worker)) {
                    return worker;
                } else {


                    ap_proxy_retry_worker_fn("BALANCER", worker, r->server);
                    if (PROXY_WORKER_IS_USABLE(worker)) {
                            return worker;
                    } else {


                        if (*worker->s->redirect) {
                            proxy_worker *rworker = NULL;
                            rworker = find_route_worker(balancer, worker->s->redirect, r);

                            if (rworker && !PROXY_WORKER_IS_USABLE(rworker)) {


                                ap_proxy_retry_worker_fn("BALANCER", rworker, r->server);
                            }
                            if (rworker && PROXY_WORKER_IS_USABLE(rworker))
                                return rworker;
                        }
                    }
                }
            }
        }
        checked_standby = checking_standby++;
    }
    return NULL;
}
