__redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, char *cmd, size_t len) {
    redisContext *c = &(ac->c);
    redisCallback cb;


    if (c->flags & REDIS_DISCONNECTING) return REDIS_ERR;
    __redisAppendCommand(c,cmd,len);


    cb.fn = fn;
    cb.privdata = privdata;
    __redisPushCallback(&ac->replies,&cb);


    if (ac->evAddWrite) ac->evAddWrite(ac->_adapter_data);

    return REDIS_OK;
}
