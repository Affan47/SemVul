__redisAsyncHandleConnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (redisCheckSocketError(c) == REDIS_ERR) {

        if (errno == EINPROGRESS)
            return REDIS_OK;

        if (ac->onConnect) ac->onConnect(ac,REDIS_ERR);
        __redisAsyncDisconnect(ac);
        return REDIS_ERR;
    }


    c->flags |= REDIS_CONNECTED;
    if (ac->onConnect) ac->onConnect(ac,REDIS_OK);
    return REDIS_OK;
}
