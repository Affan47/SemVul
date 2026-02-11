setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire) {
    long seconds = 0;

    if (expire) {
        if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
            return;
        if (seconds <= 0) {
            addReplyError(c,"invalid expire time in SETEX");
            return;
        }
    }

    if (lookupKeyWrite(c->db,key) != NULL && nx) {
        addReply(c,shared.czero);
        return;
    }
    setKey(c->db,key,val);
    server.dirty++;
    if (expire) setExpire(c->db,key,time(NULL)+seconds);
    addReply(c, nx ? shared.cone : shared.ok);
}
