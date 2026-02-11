zrtp_getPeerZid(ZrtpContext* zrtpContext, uint8_t* data) {
    if (data == NULL)
        return 0;

    if (zrtpContext && zrtpContext->zrtpEngine)
        return zrtpContext->zrtpEngine->getPeerZid(data);

    return 0;
}
