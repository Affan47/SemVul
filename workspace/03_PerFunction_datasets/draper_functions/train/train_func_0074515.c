rdbLoad(char *filename) {
    FILE *fp;
    uint32_t dbid;
    int type, rdbver;
    redisDb *db = server.db+0;
    char buf[1024];
    time_t expiretime, now = time(NULL);
    long loops = 0;

    fp = fopen(filename,"r");
    if (!fp) return REDIS_ERR;
    if (fread(buf,9,1,fp) == 0) goto eoferr;
    buf[9] = '\0';
    if (memcmp(buf,"REDIS",5) != 0) {
        fclose(fp);
        redisLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
        return REDIS_ERR;
    }
    rdbver = atoi(buf+5);
    if (rdbver < 1 || rdbver > 2) {
        fclose(fp);
        redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
        return REDIS_ERR;
    }

    startLoading(fp);
    while(1) {
        robj *key, *val;
        expiretime = -1;


        if (!(loops++ % 1000)) {
            loadingProgress(ftello(fp));
            aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
        }


        if ((type = rdbLoadType(fp)) == -1) goto eoferr;
        if (type == REDIS_EXPIRETIME) {
            if ((expiretime = rdbLoadTime(fp)) == -1) goto eoferr;

            if ((type = rdbLoadType(fp)) == -1) goto eoferr;
        }
        if (type == REDIS_EOF) break;

        if (type == REDIS_SELECTDB) {
            if ((dbid = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR)
                goto eoferr;
            if (dbid >= (unsigned)server.dbnum) {
                redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
                exit(1);
            }
            db = server.db+dbid;
            continue;
        }

        if ((key = rdbLoadStringObject(fp)) == NULL) goto eoferr;

        if ((val = rdbLoadObject(type,fp)) == NULL) goto eoferr;

        if (expiretime != -1 && expiretime < now) {
            decrRefCount(key);
            decrRefCount(val);
            continue;
        }

        dbAdd(db,key,val);


        if (expiretime != -1) setExpire(db,key,expiretime);

        decrRefCount(key);
    }
    fclose(fp);
    stopLoading();
    return REDIS_OK;

eoferr:
    redisLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
    exit(1);
    return REDIS_ERR;
}
