zrtp_DestroyWrapper(ZrtpContext* zrtpContext) {

    if (zrtpContext == NULL)
        return;

    delete zrtpContext->zrtpEngine;
    zrtpContext->zrtpEngine = NULL;

    delete zrtpContext->zrtpCallback;
    zrtpContext->zrtpCallback = NULL;

    delete zrtpContext->configure;
    zrtpContext->configure = NULL;

    delete zrtpContext;
}
