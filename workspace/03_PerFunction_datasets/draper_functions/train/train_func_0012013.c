httpOpenCacheHandler(Http *http)
{
    HttpStage     *handler, *filter;


    if ((handler = httpCreateHandler(http, "cacheHandler", HTTP_STAGE_ALL, NULL)) == 0) {
        return MPR_ERR_CANT_CREATE;
    }
    http->cacheHandler = handler;
    handler->match = matchCacheHandler;
    handler->process = processCacheHandler;


    if ((filter = httpCreateFilter(http, "cacheFilter", HTTP_STAGE_ALL, NULL)) == 0) {
        return MPR_ERR_CANT_CREATE;
    }
    http->cacheFilter = filter;
    filter->match = matchCacheFilter;
    filter->outgoingService = outgoingCacheFilterService;
    return 0;
}
