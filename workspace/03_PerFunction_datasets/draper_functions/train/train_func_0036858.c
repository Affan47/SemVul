ap_proxy_pre_request(proxy_worker **worker,
                                        proxy_balancer **balancer,
                                        request_rec *r,
                                        proxy_server_conf *conf, char **url)
{
    int access_status;

    access_status = proxy_run_pre_request(worker, balancer, r, conf, url);
    if (access_status == DECLINED && *balancer == NULL) {
        *worker = ap_proxy_get_worker(r->pool, NULL, conf, *url);
        if (*worker) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "%s: found worker %s for %s",
                          (*worker)->s->scheme, (*worker)->s->name, *url);

            *balancer = NULL;
            access_status = OK;
        }
        else if (r->proxyreq == PROXYREQ_PROXY) {
            if (conf->forward) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "*: found forward proxy worker for %s", *url);
                *balancer = NULL;
                *worker = conf->forward;
                access_status = OK;


                apr_table_setn(r->subprocess_env, "proxy-nokeepalive", "1");
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                char *ptr;
                char *ptr2;
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "*: found reverse proxy worker for %s", *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;


                apr_table_setn(r->subprocess_env, "proxy-nokeepalive", "1");


                if (apr_table_get(r->notes, "rewrite-proxy") &&
                    (ptr2 = ap_strcasestr(r->filename, "unix:")) &&
                    (ptr = ap_strchr(ptr2, '|'))) {
                    apr_uri_t urisock;
                    apr_status_t rv;
                    *ptr = '\0';
                    rv = apr_uri_parse(r->pool, ptr2, &urisock);
                    if (rv == APR_SUCCESS) {
                        char *rurl = ptr+1;
                        char *sockpath = ap_runtime_dir_relative(r->pool, urisock.path);
                        apr_table_setn(r->notes, "uds_path", sockpath);
                        *url = apr_pstrdup(r->pool, rurl);

                        memmove(r->filename+6, rurl, strlen(rurl)+1);
                        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                                      "*: rewrite of url due to UDS(%s): %s (%s)",
                                      sockpath, *url, r->filename);
                    }
                    else {
                        *ptr = '|';
                    }
                }
            }
        }
    }
    else if (access_status == DECLINED && *balancer != NULL) {

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00934)
                      "all workers are busy.  Unable to serve %s", *url);
        access_status = HTTP_SERVICE_UNAVAILABLE;
    }
    return access_status;
}
