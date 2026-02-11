cacheCreateIOJob(int type, redisDb *db, robj *key, robj *val, time_t expire) {
    iojob *j;

    j = zmalloc(sizeof(*j));
    j->type = type;
    j->db = db;
    j->key = key;
    incrRefCount(key);
    j->val = val;
    if (val) incrRefCount(val);
    j->expire = expire;

    lockThreadedIO();
    queueIOJob(j);
    pthread_cond_signal(&server.io_condvar);
    unlockThreadedIO();
}
