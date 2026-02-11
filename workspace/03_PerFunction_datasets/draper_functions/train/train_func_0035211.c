verifyAllRequestsReceived(const MockHTTP *mh, const mhServCtx_t *ctx,
                                     bool breakOnNotOnce)
{
    int i;
    apr_array_header_t *used;
    apr_pool_t *pool;
    bool result = YES;


    if (breakOnNotOnce && ctx->reqsReceived->nelts > ctx->reqMatchers->nelts) {
        appendErrMessage(mh, "More requests received than expected!\n");
        return NO;
    } else if (ctx->reqsReceived->nelts < ctx->reqMatchers->nelts) {
        appendErrMessage(mh, "Less requests received than expected!\n");
        return NO;
    }

    apr_pool_create(&pool, mh->pool);
    used = apr_array_make(mh->pool, ctx->reqsReceived->nelts,
                          sizeof(ReqMatcherRespPair_t *));;

    for (i = 0; i < ctx->reqsReceived->nelts; i++)
    {
        mhRequest_t *req = APR_ARRAY_IDX(ctx->reqsReceived, i, mhRequest_t *);
        int j;
        bool matched = NO;

        for (j = 0 ; j < ctx->reqMatchers->nelts; j++) {
            const ReqMatcherRespPair_t *pair;

            pair = APR_ARRAY_IDX(ctx->reqMatchers, j, ReqMatcherRespPair_t *);

            if (breakOnNotOnce && isArrayElement(used, pair))
                continue;

            if (_mhRequestMatcherMatch(pair->rm, req) == YES) {
                *((const ReqMatcherRespPair_t **)apr_array_push(used)) = pair;
                matched = YES;
                break;
            }
        }

        if (matched == NO) {
            apr_pool_t *tmppool;
            apr_pool_create(&tmppool, mh->pool);
            appendErrMessage(mh, "ERROR: No rule matched this request!\n");
            appendErrMessage(mh, "====================================\n");

            for (j = 0 ; j < ctx->reqMatchers->nelts; j++) {
                const ReqMatcherRespPair_t *pair;

                pair = APR_ARRAY_IDX(ctx->reqMatchers, j, ReqMatcherRespPair_t *);

                if (breakOnNotOnce && isArrayElement(used, pair))
                    continue;
                appendErrMessage(mh, "Expected request(s) with:\n");
                appendErrMessage(mh, serializeRequestMatcher(tmppool, pair->rm, req));
                if (j + 1 < ctx->reqMatchers->nelts)
                    appendErrMessage(mh, "        ------------------------\n");
            }
            appendErrMessage(mh, "---------------------------------\n");
            appendErrMessage(mh, "Actual request:\n");
            appendErrMessage(mh, serializeRequest(tmppool, req));
            appendErrMessage(mh, "=================================\n");
            apr_pool_destroy(tmppool);

            result = NO;
            break;
        }
    }

    apr_pool_destroy(pool);

    return result;
}
