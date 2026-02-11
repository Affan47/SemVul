sentinelForceHelloUpdateDictOfRedisInstances(dict *instances) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(instances);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *ri = dictGetVal(de);
        if (ri->last_pub_time >= (SENTINEL_PUBLISH_PERIOD+1))
            ri->last_pub_time -= (SENTINEL_PUBLISH_PERIOD+1);
    }
    dictReleaseIterator(di);
}
