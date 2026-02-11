getsetCommand(redisClient *c) {
    if (getGenericCommand(c) == REDIS_ERR) return;
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    dbReplace(c->db,c->argv[1],c->argv[2]);
    incrRefCount(c->argv[2]);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    removeExpire(c->db,c->argv[1]);
}
