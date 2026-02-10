rewriteAppendOnlyFileBackground(void) {
    pid_t childpid;
    long long start;

    if (server.bgrewritechildpid != -1) return REDIS_ERR;
    if (server.ds_enabled != 0) {
        redisLog(REDIS_WARNING,"BGREWRITEAOF called with diskstore enabled: AOF is not supported when diskstore is enabled. Operation not performed.");
        return REDIS_ERR;
    }
    start = ustime();
    if ((childpid = fork()) == 0) {
        char tmpfile[256];


        if (server.ipfd > 0) close(server.ipfd);
        if (server.sofd > 0) close(server.sofd);
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
            _exit(0);
        } else {
            _exit(1);
        }
    } else {

        server.stat_fork_time = ustime()-start;
        if (childpid == -1) {
            redisLog(REDIS_WARNING,
                "Can't rewrite append only file in background: fork: %s",
                strerror(errno));
            return REDIS_ERR;
        }
        redisLog(REDIS_NOTICE,
            "Background append only file rewriting started by pid %d",childpid);
        server.bgrewritechildpid = childpid;
        updateDictResizePolicy();


        server.appendseldb = -1;
        return REDIS_OK;
    }
    return REDIS_OK;
}
