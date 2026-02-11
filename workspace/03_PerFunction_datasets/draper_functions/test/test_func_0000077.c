emptyDb() {
    int j;
    long long removed = 0;

    for (j = 0; j < server.dbnum; j++) {
        removed += dictSize(server.db[j].dict);
        dictEmpty(server.db[j].dict);
        dictEmpty(server.db[j].expires);
        if (server.ds_enabled) dictEmpty(server.db[j].io_negcache);
    }
    return removed;
}
