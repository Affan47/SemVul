expireIfNeeded(redisDb *db, robj *key) {
    mstime_t when = getExpire(db,key);
    mstime_t now;

    if (when < 0) return 0;


    if (server.loading) return 0;


    now = server.lua_caller ? server.lua_time_start : mstime();


    if (server.masterhost != NULL) return now > when;


    if (now <= when) return 0;


    server.stat_expiredkeys++;
    propagateExpire(db,key);
    notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
        "expired",key,db->id);
    return dbDelete(db,key);
}
