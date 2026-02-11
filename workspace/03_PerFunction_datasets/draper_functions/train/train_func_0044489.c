zunionInterGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
    int i, num, *keys;
    REDIS_NOTUSED(cmd);
    REDIS_NOTUSED(flags);

    num = atoi(argv[2]->ptr);


    if (num > (argc-3)) {
        *numkeys = 0;
        return NULL;
    }
    keys = zmalloc(sizeof(int)*num);
    for (i = 0; i < num; i++) keys[i] = 3+i;
    *numkeys = num;
    return keys;
}
