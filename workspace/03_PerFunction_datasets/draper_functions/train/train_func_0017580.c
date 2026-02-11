matchRequest(mhRequest_t *req, mhResponse_t **resp,
             mhAction_t *action, const apr_array_header_t *matchers)
{
    int i;

    for (i = 0 ; i < matchers->nelts; i++) {
        const ReqMatcherRespPair_t *pair;

        pair = APR_ARRAY_IDX(matchers, i, ReqMatcherRespPair_t *);

        if (_mhRequestMatcherMatch(pair->rm, req) == YES) {
            *resp = pair->resp;
            *action = pair->action;
            return YES;
        }
    }

    *resp = NULL;
    return NO;
}
