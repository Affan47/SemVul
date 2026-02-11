cacheScheduleIOPushJobs(int flags) {
    time_t now = time(NULL);
    listNode *ln;
    int jobs, topush = 0, pushed = 0;


    if (server.bgsavethread != (pthread_t) -1) return 0;


    lockThreadedIO();
    jobs = listLength(server.io_newjobs);
    unlockThreadedIO();

    topush = MAX_IO_JOBS_QUEUE-jobs;
    if (topush < 0) topush = 0;
    if (topush > (signed)listLength(server.cache_io_queue))
        topush = listLength(server.cache_io_queue);

    while((ln = listFirst(server.cache_io_queue)) != NULL) {
        ioop *op = ln->value;
        struct dictEntry *de;
        robj *val;

        if (!topush) break;
        topush--;

        if (op->type != REDIS_IO_LOAD && flags & REDIS_IO_ONLYLOADS) break;


        if (op->type == REDIS_IO_SAVE && !(flags & REDIS_IO_ASAP) &&
              (now - op->ctime) < server.cache_flush_delay) break;


        if (op->type == REDIS_IO_SAVE &&
            cacheScheduleIOGetFlags(op->db,op->key) & REDIS_IO_SAVEINPROG)
        {


            if (listLength(server.cache_io_queue) > 1) {
                listDelNode(server.cache_io_queue,ln);
                listAddNodeTail(server.cache_io_queue,op);
                continue;
            } else {
                break;
            }
        }

        redisLog(REDIS_DEBUG,"Creating IO %s Job for key %s",
            op->type == REDIS_IO_LOAD ? "load" : "save", op->key->ptr);

        if (op->type == REDIS_IO_LOAD) {
            cacheCreateIOJob(REDIS_IOJOB_LOAD,op->db,op->key,NULL,0);
        } else {
            time_t expire = -1;


            de = dictFind(op->db->dict,op->key->ptr);
            if (de) {
                val = dictGetEntryVal(de);
                expire = getExpire(op->db,op->key);
            } else {


                val = NULL;
            }
            cacheCreateIOJob(REDIS_IOJOB_SAVE,op->db,op->key,val,expire);
        }

        cacheScheduleIODelFlag(op->db,op->key,op->type);
        cacheScheduleIOAddFlag(op->db,op->key,
            (op->type == REDIS_IO_LOAD) ? REDIS_IO_LOADINPROG :
                                          REDIS_IO_SAVEINPROG);


        listDelNode(server.cache_io_queue,ln);
        decrRefCount(op->key);
        zfree(op);
        pushed++;
    }
    return pushed;
}
