logStackContent(void **sp) {
    int i;
    for (i = 15; i >= 0; i--) {
        unsigned long addr = (unsigned long) sp+i;
        unsigned long val = (unsigned long) sp[i];

        if (sizeof(long) == 4)
            redisLog(REDIS_WARNING, "(%08lx) -> %08lx", addr, val);
        else
            redisLog(REDIS_WARNING, "(%016lx) -> %016lx", addr, val);
    }
}
