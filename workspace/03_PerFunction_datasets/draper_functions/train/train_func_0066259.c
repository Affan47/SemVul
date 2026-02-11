redisConnectUnix(const char *path) {
    redisContext *c;

    c = redisContextInit();
    if (c == NULL)
        return NULL;

    c->flags |= REDIS_BLOCK;
    redisContextConnectUnix(c,path,NULL);
    return c;
}
