mhNewActionForRequest(MockHTTP *mh, mhServCtx_t *ctx,
                           mhRequestMatcher_t *rm, mhAction_t action)
{
    apr_array_header_t *matchers;
    int i;

    if (ctx)
        matchers = rm->incomplete ? ctx->incompleteReqMatchers : ctx->reqMatchers;
    else
        matchers = rm->incomplete ? mh->incompleteReqMatchers : mh->reqMatchers;
    for (i = matchers->nelts - 1 ; i >= 0; i--) {
        ReqMatcherRespPair_t *pair;

        pair = APR_ARRAY_IDX(matchers, i, ReqMatcherRespPair_t *);
        if (rm == pair->rm) {
            pair->action = action;
            break;
        }
    }
}
