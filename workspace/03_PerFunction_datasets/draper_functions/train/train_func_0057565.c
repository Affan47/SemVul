latencyCommand(redisClient *c) {
    struct latencyTimeSeries *ts;

    if (!strcasecmp(c->argv[1]->ptr,"history") && c->argc == 3) {

        ts = dictFetchValue(server.latency_events,c->argv[2]->ptr);
        if (ts == NULL) {
            addReplyMultiBulkLen(c,0);
        } else {
            latencyCommandReplyWithSamples(c,ts);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"graph") && c->argc == 3) {

        sds graph;
        dictEntry *de;
        char *event;

        de = dictFind(server.latency_events,c->argv[2]->ptr);
        if (de == NULL) goto nodataerr;
        ts = dictGetVal(de);
        event = dictGetKey(de);

        graph = latencyCommandGenSparkeline(event,ts);
        addReplyBulkCString(c,graph);
        sdsfree(graph);
    } else if (!strcasecmp(c->argv[1]->ptr,"latest") && c->argc == 2) {

        latencyCommandReplyWithLatestEvents(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"doctor") && c->argc == 2) {

        sds report = createLatencyReport();

        addReplyBulkCBuffer(c,report,sdslen(report));
        sdsfree(report);
    } else if (!strcasecmp(c->argv[1]->ptr,"reset") && c->argc >= 2) {

        if (c->argc == 2) {
            addReplyLongLong(c,latencyResetEvent(NULL));
        } else {
            int j, resets = 0;

            for (j = 2; j < c->argc; j++)
                resets += latencyResetEvent(c->argv[j]->ptr);
            addReplyLongLong(c,resets);
        }
    } else {
        addReply(c,shared.syntaxerr);
    }
    return;

nodataerr:


    addReplyErrorFormat(c,
        "No samples available for event '%s'", (char*) c->argv[2]->ptr);
}
