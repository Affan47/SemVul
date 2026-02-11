zunionInterBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
    int i, num;
    REDIS_NOTUSED(cmd);

    num = atoi(argv[2]->ptr);
    if (num > (argc-3)) return;
    for (i = 0; i < num; i++) {
        waitForSwappedKey(c,argv[3+i]);
    }
}
