statMedianSvc(int interval, int which)
{
    StatCounters *f;
    StatCounters *l;
    double x;
    assert(interval > 0);
    if (interval > N_COUNT_HIST - 1)
	interval = N_COUNT_HIST - 1;
    f = &CountHist[0];
    l = &CountHist[interval];
    assert(f);
    assert(l);
    switch (which) {
    case MEDIAN_HTTP:
	x = statHistDeltaMedian(&l->client_http.all_svc_time, &f->client_http.all_svc_time);
	break;
    case MEDIAN_HIT:
	x = statHistDeltaMedian(&l->client_http.hit_svc_time, &f->client_http.hit_svc_time);
	break;
    case MEDIAN_MISS:
	x = statHistDeltaMedian(&l->client_http.miss_svc_time, &f->client_http.miss_svc_time);
	break;
    case MEDIAN_NM:
	x = statHistDeltaMedian(&l->client_http.nm_svc_time, &f->client_http.nm_svc_time);
	break;
    case MEDIAN_NH:
	x = statHistDeltaMedian(&l->client_http.nh_svc_time, &f->client_http.nh_svc_time);
	break;
    case MEDIAN_ICP_QUERY:
	x = statHistDeltaMedian(&l->icp.query_svc_time, &f->icp.query_svc_time);
	break;
    case MEDIAN_DNS:
	x = statHistDeltaMedian(&l->dns.svc_time, &f->dns.svc_time);
	break;
    default:
	debug(49, 5) ("statMedianSvc: unknown type.\n");
	x = 0;
    }
    return x;
}
