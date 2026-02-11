redisReaderGetReply(redisReader *r, void **reply) {

    if (reply != NULL)
        *reply = NULL;


    if (r->err)
        return REDIS_ERR;


    if (r->len == 0)
        return REDIS_OK;


    if (r->ridx == -1) {
        r->rstack[0].type = -1;
        r->rstack[0].elements = -1;
        r->rstack[0].idx = -1;
        r->rstack[0].obj = NULL;
        r->rstack[0].parent = NULL;
        r->rstack[0].privdata = r->privdata;
        r->ridx = 0;
    }


    while (r->ridx >= 0)
        if (processItem(r) != REDIS_OK)
            break;


    if (r->err)
        return REDIS_ERR;


    if (r->pos >= 1024) {
        r->buf = sdsrange(r->buf,r->pos,-1);
        r->pos = 0;
        r->len = sdslen(r->buf);
    }


    if (r->ridx == -1) {
        if (reply != NULL)
            *reply = r->reply;
        r->reply = NULL;
    }
    return REDIS_OK;
}
