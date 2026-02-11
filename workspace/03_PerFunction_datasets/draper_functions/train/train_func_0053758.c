rdbGenericLoadStringObject(rio *rdb, int encode) {
    int isencoded;
    uint32_t len;
    sds val;

    len = rdbLoadLen(rdb,&isencoded);
    if (isencoded) {
        switch(len) {
        case REDIS_RDB_ENC_INT8:
        case REDIS_RDB_ENC_INT16:
        case REDIS_RDB_ENC_INT32:
            return rdbLoadIntegerObject(rdb,len,encode);
        case REDIS_RDB_ENC_LZF:
            return rdbLoadLzfStringObject(rdb);
        default:
            redisPanic("Unknown RDB encoding type");
        }
    }

    if (len == REDIS_RDB_LENERR) return NULL;
    val = sdsnewlen(NULL,len);
    if (len && rioRead(rdb,val,len) == 0) {
        sdsfree(val);
        return NULL;
    }
    return createObject(REDIS_STRING,val);
}
